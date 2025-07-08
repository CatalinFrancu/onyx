#include "Stats.h"

#include "Log.h"
#include <stdio.h>

int Stats::numPositions = 0;

void Stats::report() {
  int p = numPositions;
  char unit;
  if (p >= 1'000'000) {
    p /= 1'000'000;
    unit = 'M';
  } else {
    p /= 1'000;
    unit = 'k';
  }
  fprintf(stderr, "kibitz Evaluated %d%c positions.\n", p, unit);
}
