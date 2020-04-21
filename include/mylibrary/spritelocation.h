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
  bool operator!=(const SpriteLocation& rhs) const;
  bool operator<(const Location& rhs) const;
  bool operator<=(const Location& rhs) const;
  bool operator>(const Location& rhs) const;
  bool operator>=(const Location& rhs) const;

  SpriteLocation operator+(const SpriteLocation& rhs) const;
  SpriteLocation operator%(const SpriteLocation& rhs) const;
  SpriteLocation operator-(const SpriteLocation& rhs) const;
  SpriteLocation& operator+=(const SpriteLocation& rhs);
  SpriteLocation operator-() const;

  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;

};

std::ostream& operator<<(std::ostream& os, const SpriteLocation& sprite_location);

}

#endif  // FINALPROJECT_SPRITE_LOCATION_H
