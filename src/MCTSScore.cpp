#include "MCTSScore.h"

#include "Globals.h"

MCTSScore::MCTSScore() {
  for (int i = 0; i < gNumPlayers; i++) {
    s[i] = 0;
  }
}

MCTSScore& MCTSScore::operator+=(const MCTSScore& other) {
  for (int i = 0; i < gNumPlayers; i++) {
    s[i] += other.s[i];
  }
  return *this;
}
