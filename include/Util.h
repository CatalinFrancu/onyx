#pragma once

#include <random>

class Util {
public:
  static std::mt19937 rng;

  static int min(int x, int y);
  static int max(int x, int y);
  static int popcount(int x);
  static int rand(int lo, int hi);

private:
  static std::random_device rd;

};
