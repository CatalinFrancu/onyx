#include "MoveGen.h"

#include "Log.h"
#include "Util.h"

MoveGen::MoveGen(Board* board) {
  this->board = board;
  this->player = &board->players[board->currPlayer];
  numMoves = 0;
  chipsInHand = player->chips.getTotal();
  seenChipSets.clear();
}

void MoveGen::run() {
  genTakeDifferentColorChips();
  genTakeSameColorChips();
  genReserve();
  genBuyFaceUpCard();
  genBuyReservedCard();
  addNullMove();
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
    if (board->chips[col] >= TAKE_TWO_LIMIT) {
      take[col] = 2;
      genReturns(M_TAKE_SAME);
      take[col] = 0;
    }
  }
}

void MoveGen::genReturns(int type) {
  int toReturn = Util::max(chipsInHand + take.getTotal() - MAX_CHIPS, 0);
  genReturnsRec(0, toReturn, type);
}

void MoveGen::genReturnsRec(int col, int toReturn, int type) {
  if (!toReturn) {
    pushMove(type, 0, 0);
    return;
  }
  if (col == NUM_COLORS) {
    return;
  }

  int avail = player->chips[col] + take[col];
  int maxReturn = Util::min(avail, toReturn);
  for (int r = 0; r <= maxReturn; r++) {
    take[col] -= r;
    genReturnsRec(col + 1, toReturn - r, type);
    take[col] += r;
  }
}

void MoveGen::genReserve() {
  if (player->reserve.size() < MAX_RESERVE) {
    BitSet cp = board->cards;
    while (!cp.empty()) {
      int id = cp.getAndClear();
      genReserveForCard(id);
    }
  }
}

void MoveGen::genReserveForCard(int id) {
  bool gainGold = (board->chips[NUM_COLORS] > 0);
  take.clear();
  take[NUM_COLORS] = gainGold;
  if ((chipsInHand == MAX_CHIPS) && gainGold) {
    for (int col = 0; col < NUM_COLORS; col++) {
      if (player->chips[col]) {
        take[col] = -1;
        pushMove(M_RESERVE, id, 0);
        take[col] = 0;
      }
    }
  } else {
    pushMove(M_RESERVE, id, 0);
  }
}

void MoveGen::genBuyFaceUpCard() {
  BitSet cp = board->cards;
  while (!cp.empty()) {
    int id = cp.getAndClear();
    if (player->affords(id, take)) {
      pushMove(M_BUY_FACEUP, id, 0);
    }
  }
}

void MoveGen::genBuyReservedCard() {
  for (int i = 0; i < player->reserve.size(); i++) {
    int id = player->reserve[i];
    // Other players' cards may be unknown to us.
    if ((id > 0) && player->affords(id, take)) {
      pushMove(M_BUY_RESERVE, id, i);
    }
  }
}

void MoveGen::addNullMove() {
  if (!numMoves) {
    take.clear();
    pushMove(M_TAKE_DIFFERENT, 0, 0);
  }
}

void MoveGen::pushMove(int type, int cardId, int cardPos) {
  if ((type == M_TAKE_DIFFERENT) || (type == M_TAKE_DIFFERENT)) {
    int h = take.hashCode();
    if (seenChipSets.contains(h)) {
      return;
    }
    seenChipSets.insert(h);
  }

  // Log::debug("pushing move #%d type %d cardPos %d gain %s",
  //            numMoves, type, cardPos, take.toString().c_str());
  Move& m = moves[numMoves++];
  m.type = type;
  m.cardId = cardId;
  m.cardPos = cardPos;
  m.delta.copyFrom(take);
}

Move MoveGen::getRandomMove() {
  int i = Util::rand(0, numMoves - 1);
  Move& m = moves[i];
  Log::info("chose random move type %d card #%d (pos %d) gain %s",
            m.type, m.cardId, m.cardPos, m.delta.toString().c_str());
  return m;
}
