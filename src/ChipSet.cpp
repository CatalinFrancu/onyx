#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

const int ChipSet::ZERO_MASK = 0b00111'00111'00111'00111'00111'00111;

ChipSet::ChipSet() {
  clear();
}

int ChipSet::get(int index) {
  return ((x >> (5 * index)) & 31) - 7;
}

void ChipSet::change(int index, int diff) {
  x += diff << (5 * index);
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

int ChipSet::findValue(int val) {
  int i = 0;
  while (get(i) != val) {
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
      if (s.size()) {
        s += ' ';
      }
      s += Str::chips(color, get(color));
    }
  }
  return s;
}

std::string ChipSet::toStringAsCards() {
  std::string s;
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (get(color)) {
      if (s.size()) {
        s += ' ';
      }
      s += Str::cards(color, get(color));
    }
  }
  return s;
}
