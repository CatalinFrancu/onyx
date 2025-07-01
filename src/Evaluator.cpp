#include "Evaluator.h"

#include "Log.h"
#include "MoveGen.h"
#include "Util.h"

Evaluator::Evaluator(Board* board) {
  this->board = board;
}

Move Evaluator::getBestMove() {
  MoveGen moveGen(board);
  moveGen.run();
  moveGen.randomizeMoves();

  int p = board->currPlayer;
  Score bestScore;
  bestScore.set(p, -INFIN);
  Move bestMove;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    Score score = minimax(MINIMAX_DEPTH);
    // Log::info("%s has a score of %d", m.toString().c_str(), score.calculate(p));
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
  best.set(p, -INFIN);

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
