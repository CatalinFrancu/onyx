#include "Player.h"

#include "Card.h"
#include "Log.h"
#include "Str.h"
#include "Util.h"

Player::Player() {
  points = 0;
  chips.clear();
  cards.clear();
  reserve.clear();
  numSecretReserve = 0;
  numNobles = 0;
}

void Player::readFromStdin() {
  chips.readFromStdin();
  readCards();
  readReserve();
  readNobles();
}

void Player::readCards() {
  int numCards, id;
  scanf("%d", &numCards);
  while (numCards--) {
    scanf("%d", &id);
    Card card = Card::get(id);
    cards.change(card.color, 1);
    points += card.points;
  }
}

void Player::readReserve() {
  int numReserve, id;
  scanf("%d", &numReserve);
  while (numReserve--) {
    scanf("%d", &id);
    if (id > 0) {
      reserve.toggle(id);
    } else {
      numSecretReserve++;
    }
  }
}

void Player::readNobles() {
  scanf("%d", &numNobles);
  points += numNobles * NOBLE_POINTS;

  for (int i = 0; i < numNobles; i++) {
    int ignoredNobleId;
    scanf("%d", &ignoredNobleId);
  }
}

// cost contains negative quantities (from the player's PoV)
bool Player::affords(int cardId, ChipSet& cost) {
  Card card = Card::get(cardId);
  int goldInHand = chips.get(NUM_COLORS);
  int goldNeeded = 0;

  cost = cards;
  cost.subtract(card.cost);

  // Negative values must be covered with chips or gold.
  for (int col = 0; col < NUM_COLORS; col++) {
    int needed = -cost.get(col);
    if (needed < 0) {
      cost.change(col, needed); // set to 0
    } else {
      int have = chips.get(col);
      if (have < needed) {
        cost.change(col, needed - have);
        goldNeeded += needed - have;
        if (goldNeeded > goldInHand) {
          return false;
        }
      }
    }
  }

  cost.change(NUM_COLORS, -goldNeeded);
  return true;
}

void Player::gainCard(int id) {
  Card card = Card::get(id);
  cards.change(card.color, 1);
  points += card.points;
}

void Player::loseCard(int id) {
  Card card = Card::get(id);
  cards.change(card.color, -1);
  points -= card.points;
}

int Player::staticEval() {
  if (points >= ENDGAME_POINTS) {
    return INFIN * points;
  } else {
    return (int)points * 20 + cards.getTotal() * 10 + chips.getTotal();
  }
}

void Player::print() {
  Log::debug("    Points: %hhd", points);
  Log::debug("    Nobles: %d", numNobles);
  printCardsAndChips();
  printReserve();
}

void Player::printCardsAndChips() {
  std::string s;

  for (int color = 0; color <= NUM_COLORS; color++) {
    if (cards.get(color) || chips.get(color)) {
      s += Str::cards(color, cards.get(color)) +
        Str::chips(color, chips.get(color)) +
        ' ';
    }
  }

  Log::debug("    Cards and chips: %s", s.c_str());
}

void Player::printReserve() {
  if (reserve) {
    Log::debug("    Reserve:");
    BitSet cp = reserve;
    while (cp) {
      int id = cp.getAndClear();
      Log::debug("    %s", Card::get(id).toString().c_str());
    }
  }
}
