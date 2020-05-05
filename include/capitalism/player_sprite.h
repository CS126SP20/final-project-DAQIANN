//
// Created by Daniel Qian on 4/23/20.
//

#ifndef FINALPROJECT_PLAYER_SPRITE_H
#define FINALPROJECT_PLAYER_SPRITE_H

#include "sprite_location.h"

namespace capitalism {
class PlayerSprite {
 public:
  PlayerSprite();
  PlayerSprite(const SpriteLocation& sprite_location);

  SpriteLocation GetLocation() const;
  SpriteLocation SetLocation(const SpriteLocation&);
  void SetBlocked(bool block);
  bool IsBlocked();

 private:
  SpriteLocation player_location_;
  bool is_blocked_;
};
}

#endif  // FINALPROJECT_PLAYER_SPRITE_H
