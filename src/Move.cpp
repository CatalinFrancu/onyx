#include "Move.h"

#include <sstream>

int Move::getMctsFactor() {
  return (type == M_RESERVE) ? 1 : MCTS_RESERVE_FACTOR;
}

std::string Move::toString() {
  std::stringstream ss;
  ss << "Move [type:" << (int)type;
  ss << "  card:" << (int)cardId;
  ss << "  chips:" << delta.toString();
  ss << "]";

  return ss.str();
}
