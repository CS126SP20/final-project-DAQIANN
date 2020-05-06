//
// Created by Daniel Qian on 4/19/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H
#include <string>

namespace capitalism {
struct Player {
  Player(const std::string& name, size_t score, size_t time)
      : name(name), score(score), time(time) {}
  std::string name;
  size_t score;
  size_t time;
};
}  // namespace capitalism

#endif  // FINALPROJECT_PLAYER_H
