#pragma once

#include "Constants.h"

class MCTSScore {
public:
  int s[MAX_PLAYERS];

  MCTSScore();
  MCTSScore& operator+=(const MCTSScore& other);
};
