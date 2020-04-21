// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>
#include <mylibrary/player.h>
#include <iostream>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
//using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

const char kDbPath[] = "finalgame.db";

MyApp::MyApp()
: leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
  player_name_{"test"},
  player_score_{0}
  { }

void MyApp::setup() {

}

void MyApp::update() {
//  if (top_players_.empty()) {
//    leaderboard_.AddScoreToLeaderBoard({player_name_, player_score_, NULL});
//    top_players_.push_back({player_name_, player_score_, NULL});
//  }

}

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
