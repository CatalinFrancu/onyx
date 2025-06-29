#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

char& ChipSet::operator[](int index) {
  return c[index];
}

int ChipSet::hashCode() {
  int h = 0;
  for (int color = 0; color <= NUM_COLORS; color++) {
    h = (h << 3) + (c[color] + 3);
  }
  return h;
}

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

int ChipSet::getTotal() {
  int total = 0;
  for (int color = 0; color <= NUM_COLORS; color++) {
    total += c[color];
  }
  return total;
}

void ChipSet::fromArray(const int* src) {
  for (int color = 0; color < NUM_COLORS; color++) {
    c[color] = src[color];
  }
  c[NUM_COLORS] = 0;
}

void ChipSet::copyFrom(ChipSet& src) {
  for (int color = 0; color <= NUM_COLORS; color++) {
    c[color] = src.c[color];
  }
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

int ChipSet::findAtLeast(int qty) {
  int i = 0;
  while ((i <= NUM_COLORS) && (c[i] < qty)) {
    i++;
  }
  return i;
}

int ChipSet::countValue(int val) {
  int cnt = 0;
  for (int color = 0; color <= NUM_COLORS; color++) {
    cnt += (c[color] == val);
  }
  return cnt;
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
