#include "Move.h"

#include <sstream>

std::string Move::toString() {
  std::stringstream ss;
  ss << "Move [type:" << (int)type;
  ss << "  card:" << (int)cardId;
  ss << "  (pos:" << (int)cardPos << ")";
  ss << "  chips:" << delta.toString();
  ss << "]";

  return ss.str();
}
