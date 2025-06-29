#include "Str.h"

#include "AnsiColors.h"

std::string Str::chips(int color, int count) {
  return colorRepeat(CHIP_CHAR, color, count);
}

std::string Str::cards(int color, int count) {
  return colorRepeat(CARD_CHAR, color, count);
}

std::string Str::colorRepeat(const char* msg, int color, int count) {
  std::string s(AnsiColors::CHIPS[color]);
  if (count < 0) {
    s += '-';
    count = -count;
  }
  while (count--) {
    s += msg;
  }
  s += AnsiColors::DEFAULT;
  return s;
}
