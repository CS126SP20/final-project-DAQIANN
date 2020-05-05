// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/audio.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <capitalism/leaderboard.h>
#include <capitalism/player.h>
#include <capitalism/game_engine.h>

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
  void ResetGame();

 private:
  capitalism::GameEngine engine_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  capitalism::LeaderBoard leaderboard_;
  const size_t pace_;
  const size_t size_;
  const size_t tile_size_;
  size_t temp_score_;
  bool printed_over_;
  bool paused_;
  std::vector<capitalism::Player> top_players_;
  const std::string player_name_;
  cinder::gl::Texture2dRef image_player_;
  cinder::gl::Texture2dRef image_enemy_;
  cinder::gl::Texture2dRef image_asphalt_;
  cinder::gl::Texture2dRef image_board_;
  cinder::gl::Texture2dRef image_money_;
  std::chrono::steady_clock::time_point time_begin_;
  std::chrono::steady_clock::time_point time_end_;
  std::chrono::steady_clock::time_point game_begin_;
  std::chrono::steady_clock::time_point game_end_;
  std::chrono::steady_clock::time_point pause_start_;
  std::chrono::steady_clock::time_point pause_end_;
  float total_time_paused_;
  cinder::audio::VoiceRef back_music_;
  cinder::audio::VoiceRef coin_music_;
  cinder::audio::VoiceRef game_end_music_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
