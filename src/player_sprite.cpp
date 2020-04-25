//
// Created by Daniel Qian on 4/23/20.
//

#include <mylibrary/player_sprite.h>

namespace mylibrary {
PlayerSprite::PlayerSprite() : player_location_{0,0}, visible_{true}, is_blocked_{false} {}

PlayerSprite::PlayerSprite(const SpriteLocation& player_location) : player_location_(player_location), visible_{true} {}

SpriteLocation PlayerSprite::GetLocation() const { return player_location_; }

SpriteLocation PlayerSprite::SetLocation(const mylibrary::SpriteLocation& location) {
  player_location_ = location;
  return player_location_;
}

void PlayerSprite::SetVisibility(bool visible) { visible_ = visible; }

bool PlayerSprite::IsVisible() const { return visible_; }

}