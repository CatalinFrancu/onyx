#include "BitSet.h"

#include <stdio.h>

void BitSet::clear() {
  x = 0;
}

BitSet::operator bool() const {
  return (x != 0);
}

void BitSet::toggle(int b) {
  x ^= (u128)1 << b;
}

bool BitSet::test(int b) {
  return (x >> b) & 1;
}

int BitSet::popcount() {
  return __builtin_popcountll(x >> 64) + __builtin_popcountll(x);
}

int BitSet::getAndClear() {
  int msb = 127 - clz();
  toggle(msb);
  return msb;
}

int BitSet::clz() {
  return (x >> 64)
    ? __builtin_clzll(x >> 64)
    : (64 + __builtin_clzll(x));
}
