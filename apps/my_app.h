// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/audio.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>

#include <random>
#include <string>
#include <vector>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  mylibrary::LeaderBoard leaderboard_;
  std::vector<mylibrary::Player> top_players_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
