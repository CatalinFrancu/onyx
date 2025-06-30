#pragma once

#include "Board.h"
#include "Move.h"
#include "Score.h"

class Evaluator {
public:
  Board* board;

  Evaluator(Board* board);
  Move getBestMove();

private:
  Score minimax(int depth);
};
