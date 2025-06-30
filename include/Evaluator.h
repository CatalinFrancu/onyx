#pragma once

#include "Board.h"
#include "Move.h"

class Evaluator {
public:
  Board* board;

  Evaluator(Board* board);
  Move getBestMove();

private:
  int minimax(int depth);
};
