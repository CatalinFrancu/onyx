#pragma once

#include "ChipSet.h"
#include <vector>

class Board {
public:
  void readFromStdin();
  void print();

private:
  int currPlayer;
  ChipSet chips;
  std::vector<char> cards; // convenție: cărțile de nivel mare primele
  std::vector<int> nobles;

  void readCards();
  void readNobles();
};
