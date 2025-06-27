#pragma once

#include "Constants.h"
#include <string>

class ChipSet {
public:
  char c[NUM_COLORS + 1];

  void readFromStdin();
  std::string toString();
  std::string toStringAsCards();
};
