#pragma once

#include "Constants.h"
#include <string>

class ChipSet {
public:
  char c[NUM_COLORS + 1];

  void readFromStdin();
  void clear();

  // Reads NUM_COLORS values. Sets the gold value to zero.
  void fromArray(const int* src);

  std::string toString();
  std::string toStringAsCards();
};
