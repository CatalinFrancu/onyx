#include "Player.h"

#include "Card.h"
#include "Log.h"
#include "Str.h"

Player::Player() {
  score = 0;
  chips.clear();
  cards.clear();
  reserve.clear();
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
    cards.c[card.color]++;
    score += card.points;
  }
}

void Player::readReserve() {
  int numReserve, id;
  scanf("%d", &numReserve);
  while (numReserve--) {
    scanf("%d", &id);
    reserve.push_back(id);
  }
}

void Player::readNobles() {
  scanf("%d", &numNobles);
  score += numNobles * NOBLE_POINTS;

  for (int i = 0; i < numNobles; i++) {
    int ignoredNobleId;
    scanf("%d", &ignoredNobleId);
  }
}

void Player::print() {
  Log::debug("    Score: %hhd", score);
  Log::debug("    Nobles: %d", numNobles);
  printCardsAndChips();
  printReserve();
}

void Player::printCardsAndChips() {
  std::string s;

  for (int color = 0; color <= NUM_COLORS; color++) {
    if (cards.c[color] || chips.c[color]) {
      s += Str::cards(color, cards.c[color]) +
        Str::chips(color, chips.c[color]) +
        ' ';
    }
  }

  Log::debug("    Cards and chips: %s", s.c_str());
}

void Player::printReserve() {
  if (reserve.size()) {
    Log::debug("    Reserve:");
    for (int id: reserve) {
      Log::debug("    %s", Card::get(id).toString().c_str());
    }
  }
}
