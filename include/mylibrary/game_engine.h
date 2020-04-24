//
// Created by Daniel Qian on 4/21/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

#include "direction.h"
#include "sprite.h"

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
  Sprite GetSprite() const;
  std::vector<Sprite> GetSpritesList() const;
  //PlayerSprite GetPlayer() const;

 private:
  SpriteLocation GetRandomLocation();
  std::set<SpriteLocation> GetOccupiedTiles();

 private:
  const size_t width_;
  const size_t height_;
  Sprite sprite_;
  std::vector<Sprite> sprite_list_;
  //PlayerSprite player_;
  Direction direction_;
  Direction last_direction_;
  std::mt19937 rng_;
  std::uniform_real_distribution<double> uniform_;

};

}

#endif  // FINALPROJECT_GAME_ENGINE_H
