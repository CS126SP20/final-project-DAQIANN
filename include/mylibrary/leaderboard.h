//
// Created by Daniel Qian on 4/19/20.
//
#ifndef FINALPROJECT_LEADERBOARD_H
#define FINALPROJECT_LEADERBOARD_H

#include "leaderboard.h"
#include "player.h"

#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace mylibrary {
 class LeaderBoard {
  public:
   explicit LeaderBoard(const std::string& db_path);
   void AddScoreToLeaderBoard(const Player&);
   void AddTimeToLeaderBoard(const Player&);
  private:
   sqlite::database db_;
 };
}

#endif  // FINALPROJECT_LEADERBOARD_H
