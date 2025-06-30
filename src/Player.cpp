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
    cards[card.color]++;
    points += card.points;
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
  points += numNobles * NOBLE_POINTS;

  for (int i = 0; i < numNobles; i++) {
    int ignoredNobleId;
    scanf("%d", &ignoredNobleId);
  }
}

bool Player::affords(int cardId, ChipSet& cost) {
  cost[NUM_COLORS] = 0;
  Card card = Card::get(cardId);
  for (int col = 0; col < NUM_COLORS; col++) {
    int chipsNeeded = Util::max(card.cost[col] - cards[col], 0);
    int chipsPaid = Util::min(chipsNeeded, chips[col]);
    int goldPaid = chipsNeeded - chipsPaid;
    cost[col] = -chipsPaid; // negative from the player's PoV
    cost[NUM_COLORS] -= goldPaid;
  }

  bool haveEnoughGold = (chips[NUM_COLORS] >= -cost[NUM_COLORS]);
  return haveEnoughGold;
}

void Player::gainCard(int id) {
  int color = Card::get(id).color;
  cards[color]++;
  points += Card::get(id).points;
}

void Player::loseCard(int id) {
  int color = Card::get(id).color;
  cards[color]--;
  points -= Card::get(id).points;
}

int Player::staticEval() {
  return (int)points * 20 + cards.getTotal() * 10 + chips.getTotal();
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
    if (cards[color] || chips[color]) {
      s += Str::cards(color, cards[color]) +
        Str::chips(color, chips[color]) +
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
