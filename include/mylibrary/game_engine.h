//
// Created by Daniel Qian on 4/21/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

#include <random>
#include <set>

#include "direction.h"
#include "sprite.h"
#include "player_sprite.h"

namespace mylibrary {

class GameEngine {
 public:
  //new game of size width * height
  GameEngine(size_t width, size_t height);
  GameEngine(size_t width, size_t height, unsigned seed);

  void Reset();

  void Step();

  void SetDirection(Direction);
  //size_t GetScore const;
  Sprite GetSprite(int index) const;
  std::vector<Sprite> GetSpritesList() const;
  PlayerSprite GetPlayer() const;
  void AddSprite(bool collect);
  size_t GetSpriteCount();

 private:
  std::set<SpriteLocation> GetOccupiedTiles();
  SpriteLocation GetRandomLocation();
  size_t GetScore();

 private:
  const size_t width_;
  const size_t height_;
  size_t score_ = 0;
  Sprite sprite_;
  size_t sprite_count_ = 0;
  std::vector<Sprite> sprite_list_;
  PlayerSprite player_;
  Direction direction_;
  Direction last_direction_;
  std::mt19937 rng_;
  std::uniform_real_distribution<double> uniform_;

};

}

#endif  // FINALPROJECT_GAME_ENGINE_H
