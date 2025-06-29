#include "Util.h"

int Util::min(int x, int y) {
  return (x < y) ? x : y;
}

int Util::max(int x, int y) {
  return (x > y) ? x : y;
}

int Util::popcount(int x) {
  return __builtin_popcount(x);
}
