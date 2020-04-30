// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/audio.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <mylibrary/game_engine.h>

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
  void DrawBackground();
  void DrawPlayer();
  void DrawSprites();
  void DrawGameOver();

 private:
  mylibrary::GameEngine engine_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  mylibrary::LeaderBoard leaderboard_;
  const size_t pace_;
  const size_t size_;
  const size_t tile_size_;
  bool printed_over_;
  std::vector<mylibrary::Player> top_players_;
  const std::string player_name_;
  cinder::gl::Texture2dRef my_background_;
  std::chrono::steady_clock::time_point time_begin_;
  std::chrono::steady_clock::time_point time_end_;
  std::chrono::steady_clock::time_point game_begin_;
  std::chrono::steady_clock::time_point game_end_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
