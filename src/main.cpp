#include "Board.h"
#include "Card.h"
#include "Evaluator.h"
#include "Noble.h"
#include "Stats.h"

int main(int argc, char** argv) {
  Card::createAll();
  Noble::createAll();

  Board board;
  board.readFromStdin();
  // board.print();

  Score::init(board.numPlayers);

  Evaluator eval(&board);
  Move m = eval.getBestMove();

  std::vector<int> tokens = board.translateMove(m);
  for (int tok: tokens) {
    printf("%d ", tok);
  }
  printf("\n");

  Stats::report();

  return 0;
}
