#pragma once

#include "Constants.h"
#include <string>

class ChipSet {
public:
  char c[NUM_COLORS + 1];

  char& operator[](int index);

  void readFromStdin();
  void clear();

  int getTotal();

  // Reads NUM_COLORS values. Sets the gold value to zero.
  void fromArray(const int* src);

  void copyFrom(ChipSet& src);
  int getMaskNoGold();
  void fromMask(int mask);

  // Returns NUM_COLORS + 1 if no color has >= qty chips.
  int findAtLeast(int qty);
  int countValue(int val);

  std::string toString();
  std::string toStringAsCards();
};
