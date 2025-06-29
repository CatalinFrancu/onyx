#include "Board.h"
#include "Card.h"
#include "MoveGen.h"
#include "Noble.h"

int main(int argc, char** argv) {
  Card::createAll();
  Noble::createAll();

  Board board;
  board.readFromStdin();
  board.print();

  MoveGen moveGen(&board);
  moveGen.run();

  return 0;
}
