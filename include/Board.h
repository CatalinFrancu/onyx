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
  std::vector<char> cards; // convenție: cărțile de nivel mare primele
  std::vector<char> nobles;
  std::vector<Player> players;

  void readCards();
  void readNobles();
};
