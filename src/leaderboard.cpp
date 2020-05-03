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
         "  score INTEGER NOT NULL, \n"
         "  time INTEGER NOT NULL \n"
         ");";
}

void LeaderBoard::AddToLeaderBoard(const Player& player) {
  db_ << u"insert into leaderboard (name, score, time) values (?, ?, ?);" << player.name
      << player.score
      << player.time;
}

vector<Player> LeaderBoard::GetPlayers(sqlite::database_binder *rows) {
  vector<Player> players;

  for (auto&& row : *rows) {
    string name;
    size_t score;
    size_t time;
    row >> name >> score >> time;
    Player current = {name, score, time};
    players.push_back(current);
  }

  return players;
}

vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  auto rows = db_ << "select name, score, time from leaderboard order by score desc limit ? ;"
      << limit;
  return GetPlayers(&rows);
}

vector<Player> LeaderBoard::RetrieveLongestTimes(const size_t limit) {
  auto rows = db_ << "select name, score, time from leaderboard order by time desc limit ? ;"
                  << limit;
  return GetPlayers(&rows);
}

}
