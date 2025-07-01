#include "Score.h"

#include "Constants.h"
#include "Util.h"
#include <string.h>

int Score::numPlayers;

void Score::init(int numPlayers) {
  Score::numPlayers = Util::max(numPlayers, 2);
}

Score::Score() {
  memset(s, 0, sizeof(s));
  sum = 0;
}

void Score::set(int pos, int val) {
  s[pos] = val;
  sum += val;
}

int Score::calculate(int player) {
  return s[player] * numPlayers - sum;
}

bool Score::betterThan(Score& other, int player) {
  return calculate(player) > other.calculate(player);
}
