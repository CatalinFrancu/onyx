#include "Util.h"

#include <chrono>

std::random_device Util::rd;
std::mt19937 Util::rng(rd());
u64 Util::markedTimeMillis;

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

u64 Util::getTimestampMillis() {
  const auto now = std::chrono::system_clock::now();
  auto timestamp = now.time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(timestamp).count();
}

void Util::markTime() {
  markedTimeMillis = getTimestampMillis();
}

int Util::getElapsedTimeMillis() {
  return getTimestampMillis() - markedTimeMillis;
}
