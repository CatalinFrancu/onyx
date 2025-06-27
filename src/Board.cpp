#include "Board.h"

#include "Card.h"
#include "Log.h"
#include <algorithm>
#include <stdio.h>

void Board::readFromStdin() {
  int numPlayers, ignored;
  scanf("%d %d", &numPlayers, &currPlayer); // num_players
  scanf("%d", &ignored); // round_number
  chips.readFromStdin();

  readCards();
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

void Board::print() {
  Log::debug("================ La mutare: %d\n", currPlayer);
  Log::debug("======== Jetoane:\n");
  Log::debug("    %s\n", chips.toString().c_str());
  Log::debug("======== Cărți:\n");
  Log::debug("      ID  puncte  culoare  cost\n");
  for (int id: cards) {
    Log::debug("    %s\n", Card::get(id).toString().c_str());
  }
}
