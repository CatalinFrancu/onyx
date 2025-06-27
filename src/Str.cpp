#include "Str.h"

#include "AnsiColors.h"

std::string Str::chips(int color, int count) {
  std::string s(AnsiColors::CHIPS[color]);
  while (count--) {
    s += CHIP_CHAR;
  }
  s += AnsiColors::DEFAULT;
  return s;
}
