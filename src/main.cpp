#include "Board.h"
#include "Card.h"
#include "Evaluator.h"
#include "Globals.h"
#include "Log.h"
#include "MCTSAgent.h"
#include "Noble.h"
#include "Stats.h"

int main(int argc, char** argv) {
  Card::createAll();
  Noble::createAll();

  Board board;
  board.readFromStdin();
  // board.print();
  gNumPlayers = board.numPlayers;

  Move m;

  if (STRATEGY == STRAT_MINIMAX) {
    Score::init(gNumPlayers);
    Evaluator eval(&board);
    m = eval.getBestMove();
    Stats::report();
  } else if (STRATEGY == STRAT_MCTS) {
    MCTSAgent mcts(board, MILLISECONDS_PER_MOVE);
    m = mcts.getBestMove();
  } else {
    Log::fatal("Unknown value STRATEGY = %d.", STRATEGY);
  }

  std::vector<int> tokens = board.translateMove(m);
  for (int tok: tokens) {
    printf("%d ", tok);
  }
  printf("\n");

  return 0;
}
