#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

void ChipSet::readFromStdin() {
  total = 0;
  for (int color = 0; color <= NUM_COLORS; color++) {
    scanf("%d", &c[color]);
    total += c[color];
  }
}

void ChipSet::clear() {
  for (int color = 0; color <= NUM_COLORS; color++) {
    c[color] = 0;
  }
  total = 0;
}

void ChipSet::fromArray(const int* src) {
  total = 0;
  for (int color = 0; color < NUM_COLORS; color++) {
    c[color] = src[color];
    total += c[color];
  }
  c[NUM_COLORS] = 0;
}

void ChipSet::copyFrom(ChipSet& src) {
  for (int color = 0; color <= NUM_COLORS; color++) {
    c[color] = src.c[color];
  }
  total = src.total;
}

int ChipSet::getMaskNoGold() {
  int mask = 0;
  for (int color = 0; color < NUM_COLORS; color++) {
    if (c[color]) {
      mask |= (1 << color);
    }
  }
  return mask;
}

void ChipSet::fromMask(int mask) {
  for (int color = 0; color <= NUM_COLORS; color++) {
    c[color] = (mask >> color) & 1;
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
