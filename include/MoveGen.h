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
  Move getRandomMove();

private:
  int chipsInHand;
  std::unordered_set<int> seenChipSets;

  // + means the player gains chips; - means she spends chips.
  ChipSet take;

  void genTakeDifferentColorChips();
  void genTakeSameColorChips();
  // Given that the player had player->chips to begin with, and took more
  // chips as described by cost, figure out all the possible returns.
  void genReturns(int type);
  void genReturnsRec(int col, int toReturn, int type);

  void genReserve();
  void genReserveForCard(int id, int pos);
  void genBuyFaceUpCard();
  void genBuyReservedCard();

  void pushMove(int type, int cardId, int cardPos);
};
