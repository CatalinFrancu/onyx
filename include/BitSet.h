#pragma once

#include "Constants.h"

class BitSet {
public:
  u128 x;

  void clear();
  bool empty();
  void toggle(int b);
  int getAndClear();

private:
  int clz();

};
