#include "Score.h"

#include "Util.h"

int Score::numPlayers;

void Score::init(int numPlayers) {
  Score::numPlayers = Util::max(numPlayers, 2);
}

void Score::badFor(int player) {
  for (int i = 0; i < numPlayers; i++) {
    s[i] = 0;
  }
  s[player] = -INFINITY;
}

int Score::calculate(int player) {
  int sum = s[player] * numPlayers;
  for (int i = 0; i < numPlayers; i++) {
    sum -= s[i];
  }
  return sum;
}

bool Score::betterThan(Score& other, int player) {
  return calculate(player) > other.calculate(player);
}
