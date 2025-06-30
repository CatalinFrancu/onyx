#include "Evaluator.h"

#include "MoveGen.h"
#include "Util.h"

Evaluator::Evaluator(Board* board) {
  this->board = board;
}

Move Evaluator::getBestMove() {
  MoveGen moveGen(board);
  moveGen.run();

  int p = board->currPlayer;
  Score bestScore;
  bestScore.badFor(p);
  Move bestMove;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    Score score = minimax(MINIMAX_DEPTH);
    if (score.betterThan(bestScore, p)) {
      bestScore = score;
      bestMove = m;
    }
    board->undoMove(m);
  }

  return bestMove;
}

Score Evaluator::minimax(int depth) {
  if (!depth) {
    return board->staticEval();
  }

  MoveGen moveGen(board);
  moveGen.run();

  int p = board->currPlayer;
  Score best;
  best.badFor(p);

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    Score score = minimax(depth - 1);
    if (score.betterThan(best, p)) {
      best = score;
    }
    board->undoMove(m);
  }

  return best;
}
