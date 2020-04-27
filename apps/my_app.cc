// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <mylibrary/sprite_location.h>
#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/audio.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>
#include <mylibrary/player.h>
#include <mylibrary/direction.h>
#include <iostream>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using mylibrary::SpriteLocation;
using mylibrary::Direction;
using mylibrary::Sprite;
//using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

const char kDbPath[] = "finalgame.db";

MyApp::MyApp()
: engine_{16, 16},
  leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
  pace_{70},
  player_name_{"test"},
  player_score_{0}
  { }

void MyApp::setup() {
  my_background_ = cinder::gl::Texture2d::create(loadImage(loadAsset("asphalt.jpg")));
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  engine_.AddSprite(false);
  time_begin_ = std::chrono::steady_clock::now();
  //DrawBackground();
}

void MyApp::update() {
  const auto time = system_clock::now();
//  if (top_players_.empty()) {
//    leaderboard_.AddScoreToLeaderBoard({player_name_, player_score_, NULL});
//    top_players_.push_back({player_name_, player_score_, NULL});
//  }

  //Updates the number of sprites on the board
  time_end_ = std::chrono::steady_clock::now();
  if (std::chrono::duration_cast<std::chrono::seconds>(time_end_ - time_begin_).count() > 3) {
    if (engine_.GetSpritesList().size() % 3 == 0) {
      engine_.AddSprite(true);
    } else {
      engine_.AddSprite(false);
    }
    time_begin_ = std::chrono::steady_clock::now();
  }

  //Updates the state of player
  if (time - last_time_ > std::chrono::milliseconds(pace_)) {
    engine_.Step();
    last_time_ = time;
  }
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  DrawBackground();
  DrawPlayer();
  DrawSprites();
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0,0,0));
  //cinder::gl::draw(my_background_, getWindowBounds());
}

void MyApp::DrawPlayer() {
  const SpriteLocation loc = engine_.GetPlayer().GetLocation();
  cinder::gl::color(Color(0,0,1));
  cinder::gl::drawSolidRect( Rectf(50 * loc.Row(),
                                  50 * loc.Col(),
                                  50 * loc.Row() + 50,
                                  50 * loc.Col() + 50));
  const cinder::vec2 center = getWindowCenter();
}

void MyApp::DrawSprites() {
  for (Sprite current : engine_.GetSpritesList()) {
    const SpriteLocation loc = current.GetLocation();
    if (current.IsCollectable()) {
      cinder::gl::color(Color(0,1,0));
      cinder::gl::drawSolidRect( Rectf(50 * loc.Row(),
                                       50 * loc.Col(),
                                       50 * loc.Row() + 50,
                                       50 * loc.Col() + 50));
    } else {
      cinder::gl::color(Color(1,0,0));
      cinder::gl::drawSolidRect( Rectf(50 * loc.Row(),
                                       50 * loc.Col(),
                                       50 * loc.Row() + 50,
                                       50 * loc.Col() + 50));
    }
  }
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
  }

}

}  // namespace myapp
