//
// Created by Daniel Qian on 4/23/20.
//
#include <algorithm>
#include <cstdlib>
#include <random>
#include <set>
#include <stdexcept>

#include <mylibrary/direction.h>
#include <mylibrary/game_engine.h>

namespace mylibrary {
SpriteLocation FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0,1};
    case Direction::kDown:
      return {0,-1};
    case Direction::kLeft:
      return {-1,0};
    case Direction::kRight:
      return {1,0};
  }
}

Sprite GameEngine::GetSprite() const { return sprite_; }

std::vector<Sprite> GameEngine::GetSpritesList() const { return sprite_list_; }

void GameEngine::Reset() {
  SpriteLocation sprite_location = GetRandomLocation();
}

GameEngine::GameEngine(size_t width, size_t height) : GameEngine{width, height, static_cast<unsigned>(std::rand())} {}

GameEngine::GameEngine(size_t width, size_t height, unsigned seed)
  : width_{width},
    height_{height},
    sprite_{GetRandomLocation()},
    direction_{Direction::kRight},
    last_direction_{Direction::kUp},
    rng_{seed},
    uniform_{0,1} {
  Reset();
}


}