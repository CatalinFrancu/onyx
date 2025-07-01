#pragma once

#include "Constants.h"

class BitSet {
public:
  u128 x = 0;

  void clear();
  operator bool() const;
  void toggle(int b);
  int popcount();
  int getAndClear();

private:
  int clz();

};
