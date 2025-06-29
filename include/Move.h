#pragma once

class Move {
public:
  char type;
  char cardPos;  // index in Board.cards of the card taken/bought, or NONE
  char noblePos; // index in Board.nobles of the noble gained, or NONE
  ChipSet delta; // chips gained (+) or spent (-)
};
