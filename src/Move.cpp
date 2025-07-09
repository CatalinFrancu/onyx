#include "Move.h"

#include <sstream>

int Move::getMctsWeight() {
  return MCTS_WEIGHTS[(int)type];
}

std::string Move::toString() {
  std::stringstream ss;
  ss << "Move [type:" << (int)type;
  ss << "  card:" << (int)cardId;
  ss << "  chips:" << delta.toString();
  ss << "]";

  return ss.str();
}
