#include "Board.h"

#include "Card.h"
#include "Log.h"
#include "Noble.h"
#include <algorithm>
#include <stdio.h>

void Board::readFromStdin() {
  int numPlayers, ignored;
  scanf("%d %d", &numPlayers, &currPlayer); // num_players
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
  int ignored, id;
  for (int l = 0; l < NUM_CARD_LEVELS; l++) {
    scanf("%d", &ignored); // numărul de cărți cu fața în jos
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

void Board::print() {
  Log::debug("================ La mutare: %d", currPlayer);

  Log::debug("======== Nobili:");
  for (int id: nobles) {
    Log::debug("    %s", Noble::get(id).toString().c_str());
  }

  Log::debug("======== Cărți:");
  Log::debug("      ID  puncte  culoare  cost");
  for (int id: cards) {
    Log::debug("    %s", Card::get(id).toString().c_str());
  }

  Log::debug("======== Jetoane:");
  Log::debug("    %s", chips.toString().c_str());

  for (int i = 0; i < (int)players.size(); i++) {
    Log::debug("======== Jucătorul %d:", 1 + i);
    players[i].print();
  }
}
