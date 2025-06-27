#pragma once

#include "ChipSet.h"
#include <string>

class Card {
public:
  int id;
  ChipSet cost;
  int color;
  int points;
  int level;

  static void createAll();
  static Card get(int id);
  std::string toString();

private:
  static const int DATA[NUM_CARDS + 1][NUM_COLORS + 2];
  static Card cards[NUM_CARDS + 1];

  void computeLevel();
};
