//
// Created by Daniel Qian on 4/23/20.
//
#include <capitalism/direction.h>
#include <capitalism/game_engine.h>

#include <algorithm>
#include <cstdlib>
#include <random>
#include <set>
#include <stdexcept>

namespace capitalism {
SpriteLocation FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, 1};
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {1, 0};
  }
}

Sprite GameEngine::GetSprite(int index) const { return sprite_list_[index]; }

std::vector<Sprite> GameEngine::GetSpritesList() const { return sprite_list_; }

PlayerSprite GameEngine::GetPlayer() const { return player_; }

// Creates new Sprite and adds it to the list
void GameEngine::AddSprite(bool collect) {
  Sprite new_sprite = Sprite(GetRandomLocation());
  new_sprite.SetCollectable(collect);
  sprite_list_.push_back(new_sprite);
  sprite_count_++;
}

size_t GameEngine::GetSpriteCount() { return sprite_count_; }

// Resets everything in the engine
void GameEngine::Reset() {
  player_.SetLocation(GetRandomLocation());
  sprite_list_.clear();
  sprite_count_ = 0;
  score_ = 0;
}

GameEngine::GameEngine(size_t width, size_t height)
    : GameEngine{width, height, static_cast<unsigned>(std::rand())} {}

GameEngine::GameEngine(size_t width, size_t height, unsigned seed)
    : width_{width},
      height_{height},
      score_{0},
      sprite_{GetRandomLocation()},
      sprite_count_{0},
      direction_{Direction::kRight},
      rng_{seed},
      uniform_{0, 1} {
  Reset();
}

// Decides what to do when player makes a move
void GameEngine::Step() {
  // direction_ = last_direction_;
  SpriteLocation old_loc = FromDirection(direction_);
  SpriteLocation new_loc =
      (player_.GetLocation() + old_loc) % SpriteLocation(height_, width_);
  const std::set<SpriteLocation> old_occ_tiles = GetOccupiedTiles();
  player_.SetLocation(new_loc);

  // Add did it collide with collectable or non-collectable
  const std::set<SpriteLocation> new_occ_tiles = GetOccupiedTiles();
  for (int index = 0; index < sprite_list_.size(); index++) {
    if (sprite_list_.at(index).GetLocation() == player_.GetLocation() &&
        sprite_list_.at(index).IsCollectable()) {
      score_++;
      std::cout << score_;
      sprite_list_.erase(sprite_list_.begin() + index);
    } else if (sprite_list_.at(index).GetLocation() == player_.GetLocation() &&
               !sprite_list_.at(index).IsCollectable()) {
      player_.SetBlocked(true);
    }
  }
}

// Returns the tiles that are occupied by sprites
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
  SpriteLocation final_location(0, 0);

  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      SpriteLocation loc(row, col);
      if (occupied_tiles.find(loc) != occupied_tiles.end()) {
        continue;
      }

      if (uniform_(rng_) <= 1. / (++open_space)) {
        final_location = loc;
      }
    }
  }

  return final_location;
}

size_t GameEngine::GetScore() { return score_; }

void GameEngine::SetDirection(const capitalism::Direction direction) {
  direction_ = direction;
}

}  // namespace capitalism