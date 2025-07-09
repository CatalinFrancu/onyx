#pragma once

#include "Board.h"
#include "Config.h"
#include "Constants.h"
#include "Move.h"
#include "Score.h"

class MinimaxAgent {
public:
  Board* board;
  Move moves[MINIMAX_DEPTH + 1][MAX_MOVES];
  int numPositions;

  MinimaxAgent(Board* board);
  Move getBestMove();

private:
  Score minimax(int depth);
  void report();
};
