//
// Created by Daniel Qian on 4/23/20.
//

#ifndef FINALPROJECT_PLAYER_SPRITE_H
#define FINALPROJECT_PLAYER_SPRITE_H

#include "sprite_location.h"

namespace mylibrary {
class PlayerSprite {
 public:
  PlayerSprite();
  PlayerSprite(const SpriteLocation& sprite_location);

  void IsBlocked();

  SpriteLocation GetLocation() const;
  SpriteLocation SetLocation(const SpriteLocation&);
  void SetVisibility(bool visible);
  bool IsVisible() const;

 private:
  SpriteLocation player_location_;
  bool visible_;
  bool is_blocked_;
};
}

#endif  // FINALPROJECT_PLAYER_SPRITE_H
