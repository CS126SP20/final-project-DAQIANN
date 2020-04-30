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
   void AddToLeaderBoard(const Player&);
   std::vector<Player> GetPlayers(sqlite::database_binder* rows);
   std::vector<Player> RetrieveHighScores(const size_t limit);
   std::vector<Player> RetrieveLongestTimes(const size_t limit);
  private:
   sqlite::database db_;
 };
}

#endif  // FINALPROJECT_LEADERBOARD_H
