#include "Board.h"

#include "Log.h"
#include <stdio.h>

void Board::readFromStdin() {
  int numPlayers, ignored;
  scanf("%d %d", &numPlayers, &currPlayer); // num_players
  scanf("%d", &ignored); // round_number
  chips.readFromStdin();
}

void Board::print() {
  Log::debug("================ La mutare: %d", currPlayer);
}
