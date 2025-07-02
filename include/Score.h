#pragma once

#include "Constants.h"
#include <string>

class Score {
public:
  static void init(int numPlayers);

  Score();

  void set(int pos, int val);

  // Translates this tuple into a number from player's point of view.
  int pov(int player);
  bool betterThan(Score& other, int player);

  std::string toString();

private:
  static int numPlayers;
  int s[MAX_PLAYERS];
  int sum;
};
