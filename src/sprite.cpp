//
// Created by Daniel Qian on 4/20/20.
//

#include <mylibrary/sprite.h>

namespace mylibrary {

Sprite::Sprite(const SpriteLocation& sprite_location) : sprite_location_(sprite_location) {}

SpriteLocation Sprite::GetLocation() const { return sprite_location_; }

void Sprite::SetCollectable(bool collect) { collectable_ = collect; }

bool Sprite::IsCollectable() {
  return collectable_;
}

Sprite::Sprite(const Sprite& sprite) = default;
Sprite::Sprite(mylibrary::Sprite&& sprite) noexcept = default;
Sprite& Sprite::operator=(const Sprite& sprite) = default;
Sprite& Sprite::operator=(mylibrary::Sprite&& sprite) noexcept = default;
Sprite::~Sprite() = default;

}