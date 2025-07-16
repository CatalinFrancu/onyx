#pragma once

#include "Board.h"

class MoveGen {
public:
  Board* board;
  Player* player;
  Move* moves;
  int numMoves;

  // Which noble am I winning if I do not gain a card?
  int winnableNobleNoCard;
  // Which noble am I winning if I gain a card of this color?
  int winnableNoble[NUM_COLORS];

  MoveGen(Board* board, Move* moves);
  void run();
  Move getRandomMove();
  void randomizeMoves();

private:
  int chipsInHand;

  // + means the player gains chips; - means she spends chips.
  ChipSet take;

  // Not entirely correct according to protocol: prioritizes nobles with a
  // lower ID, not nobles listed earlier in the input.
  void computeWinnableNobles();

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
