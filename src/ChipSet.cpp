#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

const int ChipSet::ZERO_MASK = 0x888888;

ChipSet::ChipSet() {
  clear();
}

int ChipSet::get(int index) {
  int offset = 4 * index;
  return ((x >> offset) & 15) - 8;
}

void ChipSet::change(int index, int diff) {
  int offset = 4 * index;
  x += diff << offset;
  sum += diff;
}

void ChipSet::readFromStdin() {
  clear();
  for (int color = 0; color <= NUM_COLORS; color++) {
    int qty;
    scanf("%d", &qty);
    change(color, qty);
  }
}

void ChipSet::clear() {
  x = ZERO_MASK;
  sum = 0;
}

int ChipSet::getTotal() {
  return sum;
}

void ChipSet::add(ChipSet& src) {
  x += src.x - ZERO_MASK;
  sum += src.sum;
}

void ChipSet::subtract(ChipSet& src) {
  x -= src.x - ZERO_MASK;
  sum -= src.sum;
}

void ChipSet::fromArray(const int* src) {
  clear();
  for (int color = 0; color < NUM_COLORS; color++) {
    change(color, src[color]);
  }
}

int ChipSet::getMaskNoGold() {
  int mask = 0;
  for (int color = 0; color < NUM_COLORS; color++) {
    if (get(color)) {
      mask |= (1 << color);
    }
  }
  return mask;
}

int ChipSet::findAtLeast(int qty) {
  int i = 0;
  while ((i <= NUM_COLORS) && (get(i) < qty)) {
    i++;
  }
  return i;
}

int ChipSet::countValue(int val) {
  int cnt = 0;
  for (int color = 0; color <= NUM_COLORS; color++) {
    cnt += (get(color) == val);
  }
  return cnt;
}

std::string ChipSet::toString() {
  std::string s;
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (get(color)) {
      s += Str::chips(color, get(color)) + ' ';
    }
  }
  return s;
}

std::string ChipSet::toStringAsCards() {
  std::string s;
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (get(color)) {
      s += Str::cards(color, get(color)) + ' ';
    }
  }
  return s;
}
