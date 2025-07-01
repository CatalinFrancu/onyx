#include "Board.h"

#include "Card.h"
#include "Log.h"
#include "Noble.h"
#include "Util.h"
#include <algorithm>
#include <stdio.h>

void Board::readFromStdin() {
  int ignored;
  scanf("%d %d", &numPlayers, &currPlayer);
  currPlayer--; // make it 0-based
  scanf("%d", &ignored); // round_number
  chips.readFromStdin();

  readCards();
  readNobles();

  for (int i = 0; i < numPlayers; i++) {
    players[i].readFromStdin();
  }
}

void Board::readCards() {
  cards.clear();
  int ignoredFaceDown, id;
  for (int l = 0; l < NUM_CARD_LEVELS; l++) {
    scanf("%d", &ignoredFaceDown);
    for (int i = 0; i < NUM_FACE_UP_CARDS_PER_LEVEL; i++) {
      scanf("%d", &id);
      if (id) {
        cards.toggle(id);
      }
    }
  }
}

void Board::readNobles() {
  int numNobles, id;
  scanf("%d", &numNobles);
  while (numNobles--) {
    scanf("%d", &id);
    nobles.toggle(id);
  }
}

void Board::makeMove(Move& m) {
  Player& p = players[currPlayer];
  p.chips.add(m.delta);
  chips.subtract(m.delta);

  switch (m.type) {
    case M_RESERVE:
      cards.toggle(m.cardId);
      p.reserve.toggle(m.cardId);
      break;
    case M_BUY_FACEUP:
      cards.toggle(m.cardId);
      p.gainCard(m.cardId);
      break;
    case M_BUY_RESERVE:
      p.reserve.toggle(m.cardId);
      p.gainCard(m.cardId);
      break;
  }

  currPlayer = (currPlayer == numPlayers - 1) ? 0 : (currPlayer + 1);
}

void Board::undoMove(Move& m) {
  currPlayer = currPlayer ? (currPlayer - 1) : (numPlayers - 1);

  Player& p = players[currPlayer];
  p.chips.subtract(m.delta);
  chips.add(m.delta);

  switch (m.type) {
    case M_RESERVE:
      cards.toggle(m.cardId);
      p.reserve.toggle(m.cardId);
      break;
    case M_BUY_FACEUP:
      cards.toggle(m.cardId);
      p.loseCard(m.cardId);
      break;
    case M_BUY_RESERVE:
      p.reserve.toggle(m.cardId);
      p.loseCard(m.cardId);
      break;
  }
}

Score Board::staticEval() {
  Score sc;
  for (int p = 0; p < numPlayers; p++) {
    sc.set(p, players[p].staticEval());
  }
  return sc;
}

std::vector<int> Board::translateMove(Move m) {
  switch (m.type) {
    case M_TAKE_DIFFERENT: return translateTakeDifferentMove(m);
    case M_TAKE_SAME: return translateTakeSameMove(m);
    case M_RESERVE: return translateReserveMove(m);
    case M_BUY_FACEUP: return translateBuyMove(m);
    case M_BUY_RESERVE: return translateBuyMove(m);
    default:
      Log::fatal("Unknown move type: %s", m.toString().c_str());
      exit(1);
  }
}

std::vector<int> Board::translateTakeDifferentMove(Move m) {
  int numTaken = m.delta.countValue(1);

  std::vector<int> v = { M_TAKE_DIFFERENT, numTaken };

  for (int col = 0; col < NUM_COLORS; col++) {
    if (m.delta.get(col) == 1) {
      v.push_back(col);
    }
  }

  return v;
}

std::vector<int> Board::translateTakeSameMove(Move m) {
  int pos = m.delta.findValue(2);

  return { M_TAKE_SAME, pos };
}

std::vector<int> Board::translateReserveMove(Move m) {
  return { M_RESERVE, m.cardId};
}

std::vector<int> Board::translateBuyMove(Move m) {
  // The protocol does not differentiate between the two M_BUY_* cases.
  return { M_BUY_FACEUP, m.cardId };
}

void Board::print() {
  Log::debug("======== Player to move: %d", currPlayer + 1);

  printNobles();
  printCards();

  Log::debug("======== Chips:");
  Log::debug("    %s", chips.toString().c_str());

  for (int i = 0; i < numPlayers; i++) {
    Log::debug("======== Player %d:", 1 + i);
    players[i].print();
  }
}

void Board::printCards() {
  Log::debug("======== Cards:");
  Log::debug("      ID  points  color  cost");

  BitSet cp = cards;
  while (cp) {
    int id = cp.getAndClear();
    Log::debug("    %s", Card::get(id).toString().c_str());
  }
}

void Board::printNobles() {
  Log::debug("======== Nobles:");
  BitSet cp = nobles;
  while (cp) {
    int id = cp.getAndClear();
    Log::debug("    %s", Noble::get(id).toString().c_str());
  }
}
