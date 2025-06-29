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
  bool affords(int cardId, ChipSet& cost);
  void gainCard(int id);
  void loseCard(int id);
  void print();

private:
  void readCards();
  void readReserve();
  void readNobles();
  void printCardsAndChips();
  void printReserve();
};
