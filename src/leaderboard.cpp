#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace mylibrary {
using std::string;
using std::vector;

LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name TEXT NOT NULL,\n"
         "  score INTEGER \n"
         ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  db_ << u"insert into leaderboard (name, score) values (?, ?);" << player.name
      << player.score;
}
}
