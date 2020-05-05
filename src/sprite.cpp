//
// Created by Daniel Qian on 4/20/20.
//

#include <capitalism/sprite.h>

namespace capitalism {

Sprite::Sprite(const SpriteLocation& sprite_location) : sprite_location_(sprite_location) {}

SpriteLocation Sprite::GetLocation() const { return sprite_location_; }

void Sprite::SetCollectable(bool collect) { collectable_ = collect; }

bool Sprite::IsCollectable() {
  return collectable_;
}

Sprite::Sprite(const Sprite& sprite) = default;
Sprite::Sprite(capitalism::Sprite&& sprite) noexcept = default;
Sprite& Sprite::operator=(const Sprite& sprite) = default;
Sprite& Sprite::operator=(capitalism::Sprite&& sprite) noexcept = default;
Sprite::~Sprite() = default;

}