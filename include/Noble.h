#pragma once

#include "ChipSet.h"
#include <string>

class Noble {
public:
  int id;
  ChipSet cost;

  static void createAll();
  static Noble get(int id);
  std::string toString();

private:
  static const int DATA[NUM_NOBLES + 1][NUM_COLORS];
  static Noble nobles[NUM_NOBLES + 1];
};
