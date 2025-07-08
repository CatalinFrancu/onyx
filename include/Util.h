#pragma once

#include "Constants.h"
#include <random>

class Util {
public:
  static std::mt19937 rng;

  static int min(int x, int y);
  static int max(int x, int y);
  static int popcount(int x);
  static int rand(int lo, int hi);

  static void markTime();
  static int getElapsedTimeMillis();

private:
  static std::random_device rd;
  static u64 markedTimeMillis;

  static u64 getTimestampMillis();
};
