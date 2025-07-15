#include "MinimaxAgent.h"

#include "Log.h"
#include "MoveGen.h"
#include "Util.h"

MinimaxAgent::MinimaxAgent(Board* board) {
  this->board = board;
  numPositions = 0;
}

Move MinimaxAgent::getBestMove() {
  MoveGen moveGen(board, moves[0]);
  moveGen.run();
  moveGen.randomizeMoves();

  int p = board->currPlayer;
  int bestScore = -INFIN * ENDGAME_POINTS  * 2;
  Move bestMove;

  for (int i = 0; i < moveGen.numMoves; i++) {
    Move& m = moveGen.moves[i];
    board->makeMove(m);
    Score score = minimax(MINIMAX_DEPTH);
    int val = score.pov(p);
    // Log::info("%s has a score of %s = %d",
    //           m.toString().c_str(), score.toString().c_str(), val);
    if (val > bestScore) {
      bestScore = val;
      bestMove = m;
    }
    board->undoMove(m);
  }

  report(bestScore);

  return bestMove;
}

Score MinimaxAgent::minimax(int depth) {
  numPositions++;

  if (!depth || board->isGameOver()) {
    return board->staticEval();
  }

  MoveGen moveGen(board, moves[depth]);
  moveGen.run();

  int p = board->currPlayer;
  Score best;
  int bestPov = -INFIN * ENDGAME_POINTS * 2;

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

void MinimaxAgent::report(int bestScore) {
  int p = numPositions;
  char unit;
  if (p >= 1'000'000) {
    p /= 1'000'000;
    unit = 'M';
  } else {
    p /= 1'000;
    unit = 'k';
  }
  fprintf(stderr, "kibitz Evaluated %d%c positions. Score %d.\n",
          p, unit, bestScore);
}
