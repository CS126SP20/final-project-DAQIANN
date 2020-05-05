//
// Created by Daniel Qian on 4/20/20.
//

#ifndef FINALPROJECT_SPRITE_H
#define FINALPROJECT_SPRITE_H

#include <capitalism/sprite_location.h>

namespace capitalism {
class Sprite {
 public:
  explicit Sprite(const SpriteLocation&);

  Sprite(const Sprite&);
  Sprite(Sprite&&) noexcept;
  Sprite& operator=(const Sprite&);
  Sprite& operator=(Sprite&&) noexcept;
  ~Sprite();

  SpriteLocation GetLocation() const;
  void SetCollectable(bool collect);
  bool IsCollectable();

 private:
  SpriteLocation sprite_location_;
  bool collectable_;
};

}

#endif  // FINALPROJECT_SPRITE_H
