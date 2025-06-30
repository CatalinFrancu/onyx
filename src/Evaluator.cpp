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
    Score score = board->staticEval();
    if (score.betterThan(bestScore, p)) {
      bestScore = score;
      bestMove = m;
    }
    board->undoMove(m);
  }

  return bestMove;
}

// int Evaluator::minimax(int depth) {
//   if (!depth) {
//     return board->staticEval();
//   }

//   MoveGen moveGen(board);
//   moveGen.run();

//   int bestScore = -INFINITY;

//   for (int i = 0; i < moveGen.numMoves; i++) {
//     Move& m = moveGen.moves[i];
//     board->makeMove(m);
//     int score = minimax(depth - 1);
//     bestScore = Util::max(bestScore, score);
//     board->undoMove(m);
//   }

//   return bestScore;
// }
