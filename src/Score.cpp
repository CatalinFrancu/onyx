#include "Score.h"

#include "Constants.h"
#include "Util.h"

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
