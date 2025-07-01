#pragma once

#include "Constants.h"
#include <string>

class ChipSet {
public:
  ChipSet();

  int get(int index);
  void change(int index, int diff);

  void readFromStdin();
  void clear();

  int getTotal();
  void add(ChipSet& src);
  void subtract(ChipSet& src);

  // Reads NUM_COLORS values. Sets the gold value to zero.
  void fromArray(const int* src);

  int getMaskNoGold();

  // Returns NUM_COLORS + 1 if no color has >= qty chips.
  int findAtLeast(int qty);
  int countValue(int val);

  std::string toString();
  std::string toStringAsCards();

private:
  static const int ZERO_MASK;

  // A 24-bit integer. Every four bits refer to one color. Quantities are
  // shifted by 8, thus quantities -8..7 are stored in x as 0..15.
  int x;
  int sum;
};
