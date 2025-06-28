#include "Noble.h"

#include <iomanip>
#include <sstream>

const int Noble::DATA[NUM_NOBLES + 1][NUM_COLORS] = {
  // red_cost, green_cost, blue_cost, white_cost, black_cost
  { /* nobles are indexed from 1 */ },
  { 4, 4, 0, 0, 0 },
  { 0, 4, 4, 0, 0 },
  { 0, 0, 4, 4, 0 },
  { 0, 0, 0, 4, 4 },
  { 4, 0, 0, 0, 4 },
  { 3, 3, 3, 0, 0 },
  { 0, 3, 3, 3, 0 },
  { 0, 0, 3, 3, 3 },
  { 3, 0, 0, 3, 3 },
  { 3, 3, 0, 0, 3 },
};

Noble Noble::nobles[NUM_NOBLES + 1];

Noble Noble::get(int id) {
  return nobles[id];
}

void Noble::createAll() {
  for (int id = 1; id <= NUM_NOBLES; id++) {
    const int* d = DATA[id];
    Noble& noble = nobles[id];
    for (int color = 0; color < NUM_COLORS; color++) {
      noble.cost.c[color] = d[color];
    } // TODO: fromArray
    noble.id = id;
  }
}

std::string Noble::toString() {
  std::stringstream ss;
  ss << "[#" << std::setw(2) << id << "]";
  ss << "    " << cost.toStringAsCards();

  return ss.str();
}
