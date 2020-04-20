//
// Created by Daniel Qian on 4/19/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H
#include <string>

namespace mylibrary {
struct Player {
  Player(const std::string& name, size_t score) : name(name), score(score) {}
  std::string name;
  size_t score;
};
}

#endif  // FINALPROJECT_PLAYER_H
