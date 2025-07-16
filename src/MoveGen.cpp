#include "MoveGen.h"

#include "Card.h"
#include "Log.h"
#include "Noble.h"
#include "Util.h"
#include <algorithm>

MoveGen::MoveGen(Board* board, Move* moves) {
  this->board = board;
  this->player = &board->players[board->currPlayer];
  this->moves = moves;
  numMoves = 0;
  chipsInHand = player->chips.getTotal();
  winnableNobleNoCard = NONE;
  for (int c = 0; c < NUM_COLORS; c++) {
    winnableNoble[c] = NONE;
  }
}

void MoveGen::run() {
  computeWinnableNobles();
  genTakeDifferentColorChips();
  genTakeSameColorChips();
  genReserve();
  genBuyFaceUpCard();
  genBuyReservedCard();
  addNullMove();
}

void MoveGen::computeWinnableNobles() {
  BitSet cp = board->nobles;
  while (cp) {
    int id = cp.getAndClear();
    Noble nob = Noble::get(id);
    int color = player->cards.missingColor(nob.cost);
    if (color == NONE) {
      winnableNobleNoCard = id;
      for (int c = 0; c < NUM_COLORS; c++) {
        winnableNoble[c] = id;
      }
    } else if (color != IMPOSSIBLE) {
      winnableNoble[color] = id;
    }
  }
}

void MoveGen::genTakeDifferentColorChips() {
  take.clear();
  int boardMask = board->chips.getMaskNoGold();
  int colorsAvail = Util::popcount(boardMask);
  int roomInHand = MAX_CHIPS - chipsInHand;

  int toTake = Util::min(MAX_TAKE, Util::min(colorsAvail, roomInHand));
  switch (toTake) {
    case 3: genTake3Chips(); break;
    case 2: genTake2Chips(); break;
    case 1: genTake1Chip(); break;
  }
}

void MoveGen::genTake3Chips() {
  // To hardcode or not to hardcode, that is the question.
  for (int i = 0; i < NUM_COLORS - 2; i++) {
    for (int j = i + 1; j < NUM_COLORS - 1; j++) {
      for (int k = j + 1; k < NUM_COLORS; k++) {
        genTake3Chips(i, j, k);
      }
    }
  }
}

void MoveGen::genTake3Chips(int i, int j, int k) {
  if (board->chips.get(i) && board->chips.get(j) && board->chips.get(k)) {
    take.change(i, 1);
    take.change(j, 1);
    take.change(k, 1);
    pushMove(M_TAKE_DIFFERENT, 0);
    take.change(i, -1);
    take.change(j, -1);
    take.change(k, -1);
  }
}

void MoveGen::genTake2Chips() {
  for (int i = 0; i < NUM_COLORS - 1; i++) {
    for (int j = i + 1; j < NUM_COLORS; j++) {
      genTake2Chips(i, j);
    }
  }
}

void MoveGen::genTake2Chips(int i, int j) {
  if (board->chips.get(i) && board->chips.get(j)) {
    take.change(i, 1);
    take.change(j, 1);
    pushMove(M_TAKE_DIFFERENT, 0);
    take.change(i, -1);
    take.change(j, -1);
  }
}

void MoveGen::genTake1Chip() {
  for (int i = 0; i < NUM_COLORS; i++) {
    genTake1Chip(i);
  }
}

void MoveGen::genTake1Chip(int i) {
  if (board->chips.get(i)) {
    take.change(i, 1);
    pushMove(M_TAKE_DIFFERENT, 0);
    take.change(i, -1);
  }
}

void MoveGen::genTakeSameColorChips() {
  if (chipsInHand + 2 <= MAX_CHIPS) {
    take.clear();
    for (int col = 0; col < NUM_COLORS; col++) {
      if (board->chips.get(col) >= TAKE_TWO_LIMIT) {
        take.change(col, 2);
        pushMove(M_TAKE_SAME, 0);
        take.change(col, -2);
      }
    }
  }
}

void MoveGen::genReserve() {
  int rsize = player->reserve.popcount() + player->numSecretReserve;
  bool hasRoomInReserve = (rsize < MAX_RESERVE);
  bool gainGold = (board->chips.get(NUM_COLORS) > 0);
  bool hasRoomForChip = !gainGold || (chipsInHand < MAX_CHIPS);

  if (hasRoomInReserve && hasRoomForChip) {
    take.clear();
    take.change(NUM_COLORS, gainGold);
    BitSet cp = board->cards;
    while (cp) {
      int id = cp.getAndClear();
      pushMove(M_RESERVE, id);
    }
  }
}

void MoveGen::genBuyFaceUpCard() {
  BitSet cp = board->cards;
  while (cp) {
    int id = cp.getAndClear();
    if (player->affords(id, take)) {
      pushMove(M_BUY_FACEUP, id);
    }
  }
}

void MoveGen::genBuyReservedCard() {
  BitSet cp = player->reserve;
  while (cp) {
    int id = cp.getAndClear();
    if (player->affords(id, take)) {
      pushMove(M_BUY_RESERVE, id);
    }
  }
}

Move MoveGen::getRandomMove() {
  int sumWeights = 0;
  for (int i = 0; i < numMoves; i++) {
    sumWeights += moves[i].getMctsWeight();
  }

  int left = Util::rand(0, sumWeights - 1);
  int i = 0;
  while (left >= moves[i].getMctsWeight()) {
    left -= moves[i].getMctsWeight();
    i++;
  }

  return moves[i];
}

void MoveGen::randomizeMoves() {
  std::shuffle(moves, moves + numMoves, Util::rng);
}

void MoveGen::addNullMove() {
  if (!numMoves) {
    take.clear();
    pushMove(M_TAKE_DIFFERENT, 0);
  }
}

void MoveGen::pushMove(int type, int cardId) {
  // Log::debug("pushing move #%d type %d gain %s",
  //            numMoves, type, take.toString().c_str());
  Move& m = moves[numMoves++];
  m.type = type;
  m.cardId = cardId;
  m.delta = take;

  m.nobleId = NONE;
  if (winnableNobleNoCard != NONE) {
    m.nobleId = winnableNobleNoCard;
  } else if (cardId &&
             (m.type == M_BUY_FACEUP || m.type == M_BUY_RESERVE)) {
    int color = Card::get(cardId).color;
    if (winnableNoble[color] != NONE) {
      m.nobleId = winnableNoble[color];
    }
  }
}
