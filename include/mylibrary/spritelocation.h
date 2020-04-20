//
// Created by Daniel Qian on 4/20/20.
//

#ifndef FINALPROJECT_SPRITE_LOCATION_H
#define FINALPROJECT_SPRITE_LOCATION_H

#include <cstddef>
#include <iostream>

namespace mylibrary {
class SpriteLocation {
 public:
  SpriteLocation(int row, int col);

  bool operator()(const SpriteLocation& lhs, const SpriteLocation& rhs) const;
  bool operator==(const SpriteLocation& rhs) const;

};
}

#endif  // FINALPROJECT_SPRITE_LOCATION_H
