#pragma once

#include "Constants.h"

class BitSet {
public:
  u128 x;

  void clear();
  operator bool() const;
  void toggle(int b);
  int popcount();
  int getAndClear();

private:
  int clz();

};
