#include "Score.h"

#include "Constants.h"
#include "Util.h"
#include <sstream>

int Score::numPlayers;

void Score::init(int numPlayers) {
  Score::numPlayers = Util::max(numPlayers, 2);
}

Score::Score() {
  sum = 0;
}

void Score::set(int pos, int val) {
  s[pos] = val;
  sum += val;
}

int Score::pov(int player) {
  return s[player] * numPlayers - sum;
}

bool Score::betterThan(Score& other, int player) {
  return pov(player) > other.pov(player);
}

std::string Score::toString() {
  std::stringstream ss;
  ss << "<";
  for (int i = 0; i < numPlayers; i++) {
    if (i) {
      ss << ',';
    }
    ss << s[i];
  }
  ss << ">";

  return ss.str();
}
