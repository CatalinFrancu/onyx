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

void ChipSet::clear() {
  for (int color = 0; color <= NUM_COLORS; color++) {
    c[color] = 0;
  }
}

void ChipSet::fromArray(const int* src) {
  for (int color = 0; color < NUM_COLORS; color++) {
    c[color] = src[color];
  }
  c[NUM_COLORS] = 0;
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
