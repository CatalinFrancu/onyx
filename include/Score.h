#pragma once

#include "Constants.h"

class Score {
public:
  static void init(int numPlayers);

  Score();

  void set(int pos, int val);
  int calculate(int player);
  bool betterThan(Score& other, int player);

private:
  static int numPlayers;
  int s[MAX_PLAYERS];
  int sum;
};
