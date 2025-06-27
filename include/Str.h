#pragma once

#include <string>

class Str {
public:
  static std::string chips(int color, int count);
  static std::string cards(int color, int count);

private:
  static std::string colorRepeat(const char* msg, int color, int count);
};
