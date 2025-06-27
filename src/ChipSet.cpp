#include "ChipSet.h"

#include "Log.h"
#include "Str.h"
#include <stdio.h>
#include <string>

void ChipSet::readFromStdin() {
  for (int color = 0; color <= NUM_COLORS; color++) {
    scanf("%d", &c[color]);
  }
}

void ChipSet::print() {
  std::string str = "    ";
  for (int color = 0; color <= NUM_COLORS; color++) {
    if (c[color]) {
      str += Str::chips(color, c[color]) + ' ';
    }
  }
  Log::debug("%s", str.c_str());
}
