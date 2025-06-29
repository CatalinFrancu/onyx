#pragma once

#include "Constants.h"
#include <string>

class ChipSet {
public:
  char c[NUM_COLORS + 1];
  char total; // sum of c

  char& operator[](int index);

  void readFromStdin();
  void clear();

  // Reads NUM_COLORS values. Sets the gold value to zero.
  void fromArray(const int* src);

  void copyFrom(ChipSet& src);
  int getMaskNoGold();
  void fromMask(int mask);

  std::string toString();
  std::string toStringAsCards();
};
