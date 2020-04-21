//
// Created by Daniel Qian on 4/20/20.
//

#ifndef FINALPROJECT_SPRITE_H
#define FINALPROJECT_SPRITE_H

#include <mylibrary/spritelocation.h>

namespace mylibrary {
class Sprite {
 public:
  explicit Sprite(const SpriteLocation&);

  Sprite(const Sprite&);
  Sprite(Sprite&&) noexcept;
  Sprite& operator=(const Sprite&);
  Sprite& operator=(Sprite&&) noexcept;
  ~Sprite();

  SpriteLocation GetLocation() const;

 private:
  SpriteLocation sprite_location_;
};

}

#endif  // FINALPROJECT_SPRITE_H
