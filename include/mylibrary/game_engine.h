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

  void SetDirection(Direction);
  //size_t GetScore const;
  Sprite GetSprite() const;

 private:
  SpriteLocation GetRandomLocation();
  std::set
};

}

#endif  // FINALPROJECT_GAME_ENGINE_H
