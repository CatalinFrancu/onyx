#pragma once

#include "Board.h"

class MoveGen {
public:
  Board* board;
  Player* player;
  Move* moves;
  int numMoves;

  MoveGen(Board* board, Move* moves);
  void run();
  Move getRandomMove();
  void randomizeMoves();

private:
  int chipsInHand;

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
