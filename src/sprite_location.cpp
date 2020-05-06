//
// Created by Daniel Qian on 4/20/20.
//
#include <capitalism/sprite_location.h>

namespace capitalism {

SpriteLocation::SpriteLocation(int row, int col) : row_(row), col_(col) {}

bool SpriteLocation::operator==(const SpriteLocation& rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}

bool SpriteLocation::operator()(const SpriteLocation& lhs, const SpriteLocation& rhs) const {
  return lhs <= rhs;
}

bool SpriteLocation::operator!=(const SpriteLocation& rhs) const {
  return !(*this == rhs);
}

bool SpriteLocation::operator<(const SpriteLocation& rhs) const {
  return row_ < rhs.row_ || (rhs.row_ >= row_ && col_ < rhs.col_);
}

bool SpriteLocation::operator<=(const SpriteLocation& rhs) const {
  return !(rhs < *this);
}

bool SpriteLocation::operator>(const SpriteLocation& rhs) const {
  return rhs < *this;
}

bool SpriteLocation::operator>=(const SpriteLocation& rhs) const {
  return !(*this < rhs);
}

SpriteLocation SpriteLocation::operator+(const SpriteLocation& rhs) const {
  return {row_ + rhs.row_, col_ + rhs.col_};
}

SpriteLocation SpriteLocation::operator-(const SpriteLocation& rhs) const {
  return *this + (-rhs);
}

SpriteLocation SpriteLocation::operator-() const { return {-row_, -col_}; }

SpriteLocation& SpriteLocation::operator+=(const SpriteLocation& rhs) {
  *this = *this + rhs;
  return *this;
}

int mod(int first, int second) {
  int third = first % second;
  return third + (third < 0 ? second : 0);
}

SpriteLocation SpriteLocation::operator%(const SpriteLocation& rhs) const {
  return {mod(row_, rhs.row_), mod(col_, rhs.col_)};
}

int SpriteLocation::Row() const { return row_; }

int SpriteLocation::Col() const { return col_; }

std::ostream& operator<<(std::ostream& os, const SpriteLocation& sprite_location) {
  os << "{row=" << sprite_location.Row() << ", col=" << sprite_location.Col()
     << "}";
  return os;
}

}  // namespace capitalism