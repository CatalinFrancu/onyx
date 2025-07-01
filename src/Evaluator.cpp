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
  int bestScore = -INFIN;
  Move bestMove;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    int score = minimax(MINIMAX_DEPTH).pov(p);
    // Log::info("%s has a score of %d", m.toString().c_str(), score);
    if (score > bestScore) {
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
  int bestPov = -INFIN;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    // Calling static eval here give us another 3% speedup or so.
    Score score = minimax(depth - 1);
    int pov = score.pov(p);
    if (pov > bestPov) {
      best = score;
      bestPov = pov;
    }
    board->undoMove(m);
  }

  return best;
}
