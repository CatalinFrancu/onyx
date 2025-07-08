#include "Board.h"
#include "Card.h"
#include "Evaluator.h"
#include "Log.h"
#include "Noble.h"
#include "Stats.h"

int main(int argc, char** argv) {
  Card::createAll();
  Noble::createAll();

  Board board;
  board.readFromStdin();
  // board.print();

  Move m;

  if (STRATEGY == STRAT_MINIMAX) {
    Score::init(board.numPlayers);
    Evaluator eval(&board);
    m = eval.getBestMove();
  } else if (STRATEGY == STRAT_MCTS) {
    Log::fatal("Strategy MCTS is not yet implemented.");
  } else {
    Log::fatal("Unknown value STRATEGY = %d.", STRATEGY);
  }

  std::vector<int> tokens = board.translateMove(m);
  for (int tok: tokens) {
    printf("%d ", tok);
  }
  printf("\n");

  Stats::report();

  return 0;
}
