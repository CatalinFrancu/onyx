#pragma once

#include "ChipSet.h"
#include <string>

class Move {
public:
  char type;
  char cardId;
  char nobleId;
  ChipSet delta; // chips gained (+) or spent (-)

  int getMctsWeight();

  std::string toString();
};
