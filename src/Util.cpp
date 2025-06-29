#include "Util.h"

std::random_device Util::rd;
std::mt19937 Util::rng(rd());

int Util::min(int x, int y) {
  return (x < y) ? x : y;
}

int Util::max(int x, int y) {
  return (x > y) ? x : y;
}

int Util::popcount(int x) {
  return __builtin_popcount(x);
}

int Util::rand(int lo, int hi) {
  std::uniform_int_distribution<> distrib(lo, hi);
  return distrib(rng);
}

void Util::insert(std::vector<char>& v, int pos, int val) {
  v.insert(v.begin() + pos, val);
}

void Util::erase(std::vector<char>& v, int pos) {
  v.erase(v.begin() + pos);
}
