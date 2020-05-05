//
// Created by Daniel Qian on 4/23/20.
//

#include <capitalism/player_sprite.h>

namespace capitalism {
PlayerSprite::PlayerSprite() : player_location_{0, 0}, is_blocked_{false} {}

PlayerSprite::PlayerSprite(const SpriteLocation& player_location)
    : player_location_(player_location) {}

SpriteLocation PlayerSprite::GetLocation() const { return player_location_; }

SpriteLocation PlayerSprite::SetLocation(const capitalism::SpriteLocation& location) {
  player_location_ = location;
  return player_location_;
}

void PlayerSprite::SetBlocked(bool block) { is_blocked_ = block; }

bool PlayerSprite::IsBlocked() { return is_blocked_; }

}  // namespace capitalism