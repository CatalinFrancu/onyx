#include "MoveGen.h"

#include "Util.h"

MoveGen::MoveGen(Board* board) {
  this->board = board;
  this->player = &board->players[board->currPlayer];
  numMoves = 0;
}

void MoveGen::run() {
  genTakeDifferentColorChips();
  genTakeSameColorChips();
  genReserve();
  genBuyFaceUpCard();
  genBuyReservedCard();
}

void MoveGen::genTakeDifferentColorChips() {
  int boardMask = board->chips.getMaskNoGold();
  int toTake = Util::min(Util::popcount(boardMask), MAX_TAKE);
  for (int mask = boardMask; mask; mask = (mask - 1) & boardMask) {
    if (Util::popcount(mask) == toTake) {
      take.fromMask(mask);
      genReturns(M_TAKE_DIFFERENT);
    }
  }
}

void MoveGen::genTakeSameColorChips() {
  take.clear();
  for (int col = 0; col < NUM_COLORS; col++) {
    if (board->chips.c[col] >= TAKE_TWO_LIMIT) {
      take.c[col] = 2;
      genReturns(M_TAKE_SAME);
      take.c[col] = 0;
    }
  }
}

void MoveGen::genReturns(int type) {
  int toReturn = Util::max(player->chips.total + take.total - MAX_CHIPS, 0);
  genReturnsRec(0, toReturn, type);
}

void MoveGen::genReturnsRec(int col, int toReturn, int type) {
  if (!toReturn) {
    pushMove(type, 0);
    return;
  }
  if (col == NUM_COLORS) {
    return;
  }

  int avail = player->chips.c[col] + take.c[col];
  int maxReturn = Util::min(avail, toReturn);
  for (int r = 0; r <= maxReturn; r++) {
    take.c[col] -= r;
    genReturnsRec(col + 1, toReturn - r, type);
    take.c[col] += r;
  }
}

void MoveGen::genReserve() {
  if (player->reserve.size() < MAX_RESERVE) {
    for (int i = 0; i < board->cards.size(); i++) {
      genReserveForCard(i);
    }
  }
}

void MoveGen::genReserveForCard(int pos) {
  bool gainGold = (board->chips.c[NUM_COLORS] >= 0);
  take.clear();
  take.c[NUM_COLORS] = gainGold;
  if ((player->chips.total == MAX_CHIPS) && gainGold) {
    for (int col = 0; col < NUM_COLORS; col++) {
      if (player->chips.c[col]) {
        take.c[col] = -1;
        pushMove(M_RESERVE, pos);
        take.c[col] = 0;
      }
    }
  } else {
    pushMove(M_RESERVE, pos);
  }
}

void MoveGen::genBuyFaceUpCard() {
  for (int i = 0; i < board->cards.size(); i++) {
    int id = board->cards[i];
    if (player->affords(id, take)) {
      pushMove(M_BUY_FACEUP, i);
    }
  }
}

void MoveGen::genBuyReservedCard() {
  for (int i = 0; i < player->reserve.size(); i++) {
    int id = player->reserve[i];
    if (player->affords(id, take)) {
      pushMove(M_BUY_RESERVE, i);
    }
  }
}

void MoveGen::pushMove(int type, int cardPos) {
  printf("pushing move type %d cardPos %d cost %s\n",
         type, cardPos, take.toString().c_str());
  Move& m = moves[numMoves++];
  m.type = type;
  m.cardPos = cardPos;
  m.delta.copyFrom(take);
}
