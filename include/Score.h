#pragma once

#include "Constants.h"

class Score {
public:
  int s[MAX_PLAYERS];

  static void init(int numPlayers);

  // Initialize it to a very bad score from player's perspective.
  void badFor(int player);

  int calculate(int player);
  bool betterThan(Score& other, int player);

private:
  static int numPlayers;
};
