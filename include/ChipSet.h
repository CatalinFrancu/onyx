#pragma once

#include "Constants.h"

class ChipSet {
public:
  char c[NUM_COLORS + 1];

  void readFromStdin();
  void print();
};
