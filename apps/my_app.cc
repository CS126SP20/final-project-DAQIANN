// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <capitalism/direction.h>
#include <capitalism/player.h>
#include <capitalism/sprite_location.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace myapp {

using capitalism::Direction;
using capitalism::Sprite;
using capitalism::SpriteLocation;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::string;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

const char kDbPath[] = "finalgame.db";
const char kTheFont[] = "Arial";

DECLARE_uint32(size);
DECLARE_uint32(tilesize);
DECLARE_uint32(pace);
DECLARE_string(name);

MyApp::MyApp()
    : engine_{FLAGS_size, FLAGS_size},
      leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      pace_{FLAGS_pace},
      size_{FLAGS_size},
      tile_size_{FLAGS_tilesize},
      temp_score_{0},
      printed_over_{false},
      paused_{false},
      player_name_{FLAGS_name} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  // Images used in the game
  image_player_ =
      cinder::gl::Texture2d::create(loadImage(loadAsset("secondsprite.jpg")));
  image_enemy_ =
      cinder::gl::Texture2d::create(loadImage(loadAsset("bombsprite.png")));
  image_asphalt_ =
      cinder::gl::Texture2d::create(loadImage(loadAsset("moreasphalt.jpg")));
  image_money_ =
      cinder::gl::Texture2d::create(loadImage(loadAsset("money.png")));
  image_board_ =
      cinder::gl::Texture2d::create(loadImage(loadAsset("BlackBoard.jpg")));

  // Counts time during gameplay
  time_begin_ = std::chrono::steady_clock::now();
  game_begin_ = std::chrono::steady_clock::now();
  total_time_paused_ = 0.0;

  // Background music
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("BackgroundMus.mp3"));
  back_music_ = cinder::audio::Voice::create(sourceFile);
  back_music_->start();

  // Music for when collecting a green coin
  cinder::audio::SourceFileRef sourceFileTwo =
      cinder::audio::load(cinder::app::loadAsset("CatchCoin.mp3"));
  coin_music_ = cinder::audio::Voice::create(sourceFileTwo);
}

void MyApp::update() {
  // Collects the high scores/times of the leaderboard
  if (engine_.GetPlayer().IsBlocked()) {
    game_end_ = std::chrono::steady_clock::now();
    if (top_players_.empty()) {
      cinder::audio::SourceFileRef sourceFile =
          cinder::audio::load(cinder::app::loadAsset("BreakMetal.mp3"));
      game_end_music_ = cinder::audio::Voice::create(sourceFile);
      game_end_music_->start();
      leaderboard_.AddToLeaderBoard(
          {player_name_, engine_.GetScore(),
           static_cast<size_t>(
               (std::chrono::duration_cast<std::chrono::microseconds>(game_end_ - game_begin_).count() / 1000000) - total_time_paused_)});
      top_players_ = leaderboard_.RetrieveLongestTimes(3);
      assert(!top_players_.empty());
    }
    return;
  }

  // If background music stops have it start again
  if (!(back_music_->isPlaying())) {
    back_music_->start();
  }

  // Doesn't update when paused
  if (paused_) {
    return;
  }
  const auto time = system_clock::now();

  // Updates the number of sprites on the board
  time_end_ = std::chrono::steady_clock::now();
  if (std::chrono::duration_cast<std::chrono::seconds>(time_end_ - time_begin_)
          .count() > 2) {
    if (engine_.GetSpriteCount() % 3 == 0) {
      engine_.AddSprite(true);
    } else {
      engine_.AddSprite(false);
    }
    time_begin_ = std::chrono::steady_clock::now();
  }

  // Plays sound when collects green sprite with money symbol
  if (engine_.GetScore() - temp_score_ != 0) {
    coin_music_->start();
    temp_score_ = engine_.GetScore();
  }

  // Updates the state of player
  if (time - last_time_ > std::chrono::milliseconds(pace_)) {
    engine_.Step();
    last_time_ = time;
  }
}

void MyApp::draw() {
  if (engine_.GetPlayer().IsBlocked()) {
    if (!printed_over_) {
      cinder::gl::clear();
      cinder::gl::disableDepthRead();
      cinder::gl::disableDepthRead();
      cinder::gl::enableAlphaBlending();
      cinder::gl::color(Color(1, 1, 1));
      cinder::gl::draw(image_board_, getWindowBounds());
    }
    DrawGameOver();
    return;
  }

  if (paused_) {
    return;
  }

  DrawBackground();
  DrawPlayer();
  DrawSprites();
}

template <typename C>
void Print(const string& text, const C& color, const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(kTheFont, 40))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawBackground() {
  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthRead();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(Color(1, 1, 1));
  cinder::gl::draw(image_asphalt_, getWindowBounds());
}

void MyApp::DrawPlayer() {
  const SpriteLocation loc = engine_.GetPlayer().GetLocation();
  cinder::gl::color(Color(1, 1, 1));
  cinder::gl::draw(image_player_,
                   Rectf(tile_size_ * loc.Row(), tile_size_ * loc.Col(),
                         tile_size_ * loc.Row() + tile_size_,
                         tile_size_ * loc.Col() + tile_size_));
  const cinder::vec2 center = getWindowCenter();
}

void MyApp::DrawSprites() {
  for (Sprite current : engine_.GetSpritesList()) {
    const SpriteLocation loc = current.GetLocation();
    if (current.IsCollectable()) {
      cinder::gl::color(Color(0, 1, 0));
      cinder::gl::draw(image_money_,
                       Rectf(tile_size_ * loc.Row(), tile_size_ * loc.Col(),
                             tile_size_ * loc.Row() + tile_size_,
                             tile_size_ * loc.Col() + tile_size_));

    } else {
      cinder::gl::color(Color(1, 0, 0));
      cinder::gl::draw(image_enemy_,
                       Rectf(tile_size_ * loc.Row(), tile_size_ * loc.Col(),
                             tile_size_ * loc.Row() + tile_size_,
                             tile_size_ * loc.Col() + tile_size_));
    }
  }
}

void MyApp::DrawGameOver() {
  if (printed_over_ || top_players_.empty()) {
    return;
  }
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color_red = Color(1, 0, 0);
  Print("Game Over", color_red, size, center);

  std::stringstream ss;
  ss << "High Values: ";
  Print(ss.str(), color_red, size, {center.x, center.y + (++row) * 50});
  for (const capitalism::Player& player : top_players_) {
    std::stringstream ss_new;
    ss_new << player.name << " - " << player.score << " - " << player.time
           << " seconds";
    Print(ss_new.str(), color_red, size, {center.x, center.y + (++row) * 50});
  }

  printed_over_ = true;
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_w:
    case KeyEvent::KEY_UP: {
      engine_.SetDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_s:
    case KeyEvent::KEY_DOWN: {
      engine_.SetDirection(Direction::kDown);
      break;
    }
    case KeyEvent::KEY_d:
    case KeyEvent::KEY_RIGHT: {
      engine_.SetDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_a:
    case KeyEvent::KEY_LEFT: {
      engine_.SetDirection(Direction::kLeft);
      break;
    }

    case KeyEvent::KEY_p: {
      if (!paused_) {
        pause_start_ = std::chrono::steady_clock::now();
      } else if (paused_) {
        pause_end_ = std::chrono::steady_clock::now();
        total_time_paused_ +=
            std::chrono::duration_cast<std::chrono::microseconds>(pause_end_ - pause_start_).count() / 1000000;
      }
      paused_ = !paused_;
      break;
    }

    case KeyEvent::KEY_r: {
      ResetGame();
      break;
    }

    case KeyEvent::KEY_q: {
      std::exit(0);
    }
  }
}

void MyApp::ResetGame() {
  engine_.Reset();
  printed_over_ = false;
  top_players_.clear();
  game_begin_ = std::chrono::steady_clock::now();
  time_begin_ = std::chrono::steady_clock::now();
  total_time_paused_ = 0.0;
  temp_score_ = 0;
}

}  // namespace myapp
