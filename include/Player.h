#pragma once

#include "ChipSet.h"
#include <vector>

class Player {
public:
  char score;
  ChipSet chips;
  ChipSet cards;
  std::vector<char> reserve;
  int numNobles;

  Player();
  void readFromStdin();
  void print();

private:
  void readCards();
  void readReserve();
  void readNobles();
  void printCardsAndChips();
  void printReserve();
};
