#pragma once

#include "BitSet.h"
#include "ChipSet.h"

class Player {
public:
  char points;
  ChipSet chips;
  ChipSet cards;
  BitSet reserve;
  int numSecretReserve;
  int numNobles;

  Player();
  void readFromStdin();
  bool affords(int cardId, ChipSet& cost);
  void gainCard(int id);
  void loseCard(int id);
  int staticEval();
  void print();

private:
  void readCards();
  void readReserve();
  void readNobles();
  void printCardsAndChips();
  void printReserve();
};
