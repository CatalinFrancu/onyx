#include "Board.h"

#include "Card.h"
#include "Log.h"
#include "Noble.h"
#include "Util.h"
#include <algorithm>
#include <stdio.h>

void Board::readFromStdin() {
  int numPlayers, ignored;
  scanf("%d %d", &numPlayers, &currPlayer); // num_players
  currPlayer--; // make it 0-based
  scanf("%d", &ignored); // round_number
  chips.readFromStdin();

  readCards();
  readNobles();

  while (numPlayers--) {
    Player p;
    p.readFromStdin();
    players.push_back(p);
  }
}

void Board::readCards() {
  int ignoredFaceDown, id;
  for (int l = 0; l < NUM_CARD_LEVELS; l++) {
    scanf("%d", &ignoredFaceDown);
    for (int i = 0; i < NUM_FACE_UP_CARDS_PER_LEVEL; i++) {
      scanf("%d", &id);
      if (id) {
        cards.push_back(id);
      }
    }
  }
  std::reverse(cards.begin(), cards.end());
}

void Board::readNobles() {
  int numNobles, id;
  scanf("%d", &numNobles);
  while (numNobles--) {
    scanf("%d", &id);
    nobles.push_back(id);
  }
}

void Board::makeMove(Move& m) {
  Player& p = players[currPlayer];
  p.chips.add(m.delta);
  chips.subtract(m.delta);

  switch (m.type) {
    case M_RESERVE:
      Util::erase(cards, m.cardPos);
      p.reserve.push_back(m.cardId);
      break;
    case M_BUY_FACEUP:
      Util::erase(cards, m.cardPos);
      p.gainCard(m.cardId);
      break;
    case M_BUY_RESERVE:
      Util::erase(p.reserve, m.cardPos);
      p.gainCard(m.cardId);
      break;
  }

  currPlayer = (currPlayer + 1) % players.size();
}

void Board::undoMove(Move& m) {
  currPlayer = (currPlayer + players.size() - 1) % players.size();

  Player& p = players[currPlayer];
  p.chips.subtract(m.delta);
  chips.add(m.delta);

  switch (m.type) {
    case M_RESERVE:
      Util::insert(cards, m.cardPos, m.cardId);
      p.reserve.pop_back();
      break;
    case M_BUY_FACEUP:
      Util::insert(cards, m.cardPos, m.cardId);
      p.loseCard(m.cardId);
      break;
    case M_BUY_RESERVE:
      Util::insert(p.reserve, m.cardPos, m.cardId);
      p.loseCard(m.cardId);
      break;
  }
}

int Board::staticEval() {
  int result = 0;
  int n = Util::max(players.size(), 2);
  // We are trying to figure out the quality of the position for the player
  // who has *just moved*.
  int prev = (currPlayer + players.size() - 1) % players.size();

  for (int p = 0; p < players.size(); p++) {
    int x = players[p].staticEval();
    if (p == prev) {
      result += x * (n - 1);
    } else {
      result -= x;
    }
  }
  return result;
}

std::vector<int> Board::translateMove(Move m) {
  switch (m.type) {
    case M_TAKE_DIFFERENT: return translateTakeDifferentMove(m);
    case M_TAKE_SAME: return translateTakeSameMove(m);
    case M_RESERVE: return translateReserveMove(m);
    case M_BUY_FACEUP: return translateBuyFaceupMove(m);
    case M_BUY_RESERVE: return translateBuyReserveMove(m);
    default: exit(1);
  }
}

std::vector<int> Board::translateTakeDifferentMove(Move m) {
  int numTaken = m.delta.countValue(1);

  std::vector<int> v;
  v.push_back(M_TAKE_DIFFERENT);
  v.push_back(numTaken);

  for (int col = 0; col < NUM_COLORS; col++) {
    if (m.delta[col] == 1) {
      v.push_back(col);
    }
  }

  translateReturns(m, v);
  return v;
}

std::vector<int> Board::translateTakeSameMove(Move m) {
  std::vector<int> v;
  v.push_back(M_TAKE_SAME);

  // There may not be a value of 2, or even 1, due to returns.
  int pos = m.delta.findAtLeast(1);

  if (pos >= NUM_COLORS) {
    pos = chips.findAtLeast(TAKE_TWO_LIMIT);
  }

  v.push_back(pos);
  m.delta[pos] -= 2;
  translateReturns(m, v);

  return v;
}

std::vector<int> Board::translateReserveMove(Move m) {
  std::vector<int> v;
  v.push_back(M_RESERVE);
  v.push_back(cards[m.cardPos]);
  translateReturns(m, v);
  return v;
}

std::vector<int> Board::translateBuyFaceupMove(Move m) {
  std::vector<int> v;
  v.push_back(M_BUY_FACEUP);
  v.push_back(cards[m.cardPos]);
  return v;
}

std::vector<int> Board::translateBuyReserveMove(Move m) {
  std::vector<int> v;
  // The protocol does not differentiate between the two M_BUY_* cases.
  v.push_back(M_BUY_FACEUP);
  v.push_back(players[currPlayer].reserve[m.cardPos]);
  return v;
}

void Board::translateReturns(Move m, std::vector<int>& v) {
  for (int col = 0; col < NUM_COLORS; col++) {
    for (int i = 0; i < -m.delta[col]; i++) {
      v.push_back(col);
    }
  }
}

void Board::print() {
  Log::debug("======== Player to move: %d", currPlayer + 1);

  Log::debug("======== Nobles:");
  for (int id: nobles) {
    Log::debug("    %s", Noble::get(id).toString().c_str());
  }

  Log::debug("======== Cards:");
  Log::debug("      ID  points  color  cost");
  for (int id: cards) {
    Log::debug("    %s", Card::get(id).toString().c_str());
  }

  Log::debug("======== Chips:");
  Log::debug("    %s", chips.toString().c_str());

  for (int i = 0; i < (int)players.size(); i++) {
    Log::debug("======== Player %d:", 1 + i);
    players[i].print();
  }
}
