#pragma once

#include "Constants.h"

class MCTSScore {
public:
  double s[MAX_PLAYERS];

  MCTSScore();
  MCTSScore& operator+=(const MCTSScore& other);
};
