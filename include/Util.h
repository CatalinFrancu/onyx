#pragma once

#include <random>

class Util {
public:
  static int min(int x, int y);
  static int max(int x, int y);
  static int popcount(int x);
  static int rand(int lo, int hi);
  static void insert(std::vector<char>& v, int pos, int val);
  static void erase(std::vector<char>& v, int pos);

private:
  static std::random_device rd;
  static std::mt19937 rng;

};
