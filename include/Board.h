#pragma once

#include "ChipSet.h"
#include "Player.h"
#include <vector>

class Board {
public:
  void readFromStdin();
  void print();

private:
  int currPlayer;
  ChipSet chips;
  std::vector<char> cards; // high-level cards go first
  std::vector<char> nobles;
  std::vector<Player> players;

  void readCards();
  void readNobles();
};
