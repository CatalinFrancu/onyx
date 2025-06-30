#include "Evaluator.h"

#include "MoveGen.h"

Evaluator::Evaluator(Board* board) {
  this->board = board;
}

Move Evaluator::getBestMove() {
  MoveGen moveGen(board);
  moveGen.run();

  int bestScore = -1'000'000;
  Move bestMove;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    int score = board->staticEval();
    if (score > bestScore) {
      bestScore = score;
      bestMove = m;
    }
    board->undoMove(m);
  }
  return bestMove;
}
