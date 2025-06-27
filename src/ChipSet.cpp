#include "ChipSet.h"

#include <stdio.h>

void ChipSet::readFromStdin() {
  for (int color = 0; color <= NUM_COLORS; color++) {
    scanf("%d", &c[color]);
  }
}
