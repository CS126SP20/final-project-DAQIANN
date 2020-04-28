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
      return {0,-1};
    case Direction::kDown:
      return {0,1};
    case Direction::kLeft:
      return {-1,0};
    case Direction::kRight:
      return {1,0};
  }
}

Sprite GameEngine::GetSprite(int index) const { return sprite_list_[index]; }

std::vector<Sprite> GameEngine::GetSpritesList() const { return sprite_list_; }

PlayerSprite GameEngine::GetPlayer() const { return player_; }

void GameEngine::AddSprite(bool collect) {
  Sprite new_sprite = Sprite(GetRandomLocation());
  new_sprite.SetCollectable(collect);
  sprite_list_.push_back(new_sprite);
}

void GameEngine::Reset() {
  player_.SetLocation(GetRandomLocation());
}

GameEngine::GameEngine(size_t width, size_t height) : GameEngine{width, height, static_cast<unsigned>(std::rand())} {}

GameEngine::GameEngine(size_t width, size_t height, unsigned seed)
    : width_{width},
      height_{height},
      score_{0},
      sprite_{GetRandomLocation()},
      direction_{Direction::kRight},
      last_direction_{Direction::kUp},
      rng_{seed},
      uniform_{0,1} {
  Reset();
}

void GameEngine::Step() {
  //direction_ = last_direction_;
  SpriteLocation old_loc = FromDirection(direction_);
  SpriteLocation new_loc = (player_.GetLocation() + old_loc) % SpriteLocation(height_, width_);
  const std::set<SpriteLocation> old_occ_tiles = GetOccupiedTiles();

  SpriteLocation old = player_.GetLocation();
  player_.SetLocation(new_loc);
  last_direction_ = direction_;

  //Add did it collide with collectable or non-collectable
  const std::set<SpriteLocation> new_occ_tiles = GetOccupiedTiles();
  for (Sprite current : sprite_list_) {
    if (current.GetLocation() == player_.GetLocation() && current.IsCollectable()) {
      score_++;
      std::cout << score_;
      current.SetCollectable(false);
    } else if (current.GetLocation() == player_.GetLocation() && !current.IsCollectable()) {
      player_.SetBlocked(true);
    }
  }

}

std::set<SpriteLocation> GameEngine::GetOccupiedTiles() {
  std::set<SpriteLocation> occupied_tiles;
  for (const Sprite current : sprite_list_) {
    occupied_tiles.insert(current.GetLocation());
  }

  return occupied_tiles;
}

SpriteLocation GameEngine::GetRandomLocation() {
  std::set<SpriteLocation> occupied_tiles = GetOccupiedTiles();
  int open_space = 0;
  SpriteLocation final_location(0,0);

  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      SpriteLocation loc(row, col);
      if (occupied_tiles.find(loc) != occupied_tiles.end()) {
        continue;
      }

      if (uniform_(rng_) <= 1./(++open_space)) {
        final_location = loc;
      }
    }
  }

  return final_location;
}

size_t GameEngine::GetScore() {
  return score_;
}

void GameEngine::SetDirection(const mylibrary::Direction direction) {
  direction_ = direction;
}

}