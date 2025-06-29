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
    pushMove(type, 0);
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
    for (int i = 0; i < board->cards.size(); i++) {
      genReserveForCard(i);
    }
  }
}

void MoveGen::genReserveForCard(int pos) {
  bool gainGold = (board->chips[NUM_COLORS] >= 0);
  take.clear();
  take[NUM_COLORS] = gainGold;
  if ((chipsInHand == MAX_CHIPS) && gainGold) {
    for (int col = 0; col < NUM_COLORS; col++) {
      if (player->chips[col]) {
        take[col] = -1;
        pushMove(M_RESERVE, pos);
        take[col] = 0;
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
  m.cardPos = cardPos;
  m.delta.copyFrom(take);
}

Move MoveGen::getRandomMove() {
  int i = Util::rand(0, numMoves - 1);
  Move& m = moves[i];
  Log::info("chose random move type %d cardPos %d gain %s",
            m.type, m.cardPos, m.delta.toString().c_str());
  return m;
}
