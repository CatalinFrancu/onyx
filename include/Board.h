#pragma once

#include "ChipSet.h"
#include "Move.h"
#include "Player.h"
#include <vector>

class Board {
public:
  int currPlayer;
  ChipSet chips;
  std::vector<char> cards; // high-level cards go first
  std::vector<char> nobles;
  std::vector<Player> players;

  void readFromStdin();
  Player* getCurrentPlayer();
  void print();

private:
  void readCards();
  void readNobles();
};
