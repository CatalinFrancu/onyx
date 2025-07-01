#pragma once

#include "Board.h"

#include <unordered_set>

class MoveGen {
public:
  Board* board;
  Player* player;
  Move moves[MAX_MOVES];
  int numMoves;

  MoveGen(Board* board);
  void run();
  void randomizeMoves();

private:
  int chipsInHand;
  std::unordered_set<int> seenChipSets;

  // + means the player gains chips; - means she spends chips.
  ChipSet take;

  void genTakeDifferentColorChips();
  void genTake3Chips();
  void genTake3Chips(int i, int j, int k);
  void genTake2Chips();
  void genTake2Chips(int i, int j);
  void genTake1Chip();
  void genTake1Chip(int i);
  void genTakeSameColorChips();
  void genReserve();
  void genBuyFaceUpCard();
  void genBuyReservedCard();

  // When there are no other moves.
  void addNullMove();

  void pushMove(int type, int cardId);
};
