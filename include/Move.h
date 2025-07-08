#pragma once

#include "ChipSet.h"
#include <string>

class Move {
public:
  char type;
  char cardId;
  char noblePos; // index in Board.nobles of the noble gained
  ChipSet delta; // chips gained (+) or spent (-)

  int getMctsFactor();

  std::string toString();
};
