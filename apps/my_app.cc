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
  pace_{50},
  player_name_{"test"},
  player_score_{0}
  { }

void MyApp::setup() {
  my_background_ = cinder::gl::Texture2d::create(loadImage(loadAsset("GrassBackground.jpg")));
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  //DrawBackground();
}

void MyApp::update() {
  const auto time = system_clock::now();
//  if (top_players_.empty()) {
//    leaderboard_.AddScoreToLeaderBoard({player_name_, player_score_, NULL});
//    top_players_.push_back({player_name_, player_score_, NULL});
//  }
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
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0,0,0));
  //cinder::gl::draw(my_background_, getWindowBounds());
}

void MyApp::DrawPlayer() {
  const SpriteLocation loc = engine_.GetPlayer().GetLocation();
  cinder::gl::color(Color(0,0,1));
  cinder::gl::drawSolidRect(Rectf(50 * loc.Row(),
                                  50 * loc.Col(),
                                  50 * loc.Row() + 50,
                                  50 * loc.Col() + 50));
  const cinder::vec2 center = getWindowCenter();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kDown);
      break;
    }
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kLeft);
      break;
    }
  }

}

}  // namespace myapp
