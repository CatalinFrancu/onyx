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

  int findValue(int val); // assumes the value exists
  int countValue(int val);

  std::string toString();
  std::string toStringAsCards();

private:
  static const int ZERO_MASK;

  // A 30-bit integer. Every five bits refer to one color. Quantities are
  // shifted by 7, thus quantities -7..24 are stored in x as 0..31.
  //
  // This is should be enough even in the worst case. For example, when
  // computing affordability, we add chips and cards. There are 18 cards and 7
  // chips of each color and their sum is 25 > 24. However, those 18 cards are
  // worth 28 points so the game would be over.
  int x;
  int sum;
};
