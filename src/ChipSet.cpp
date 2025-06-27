#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

void ChipSet::readFromStdin() {
  for (int color = 0; color <= NUM_COLORS; color++) {
    scanf("%d", &c[color]);
  }
}

std::string ChipSet::toString() {
  std::string s;
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (c[color]) {
      s += Str::chips(color, c[color]) + ' ';
    }
  }
  return s;
}

std::string ChipSet::toStringAsCards() {
  std::string s;
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (c[color]) {
      s += Str::cards(color, c[color]) + ' ';
    }
  }
  return s;
}
