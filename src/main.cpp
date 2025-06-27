#include "Board.h"
#include "Card.h"
#include "Noble.h"

int main(int argc, char** argv) {
  Card::createAll();
  Noble::createAll();

  Board board;
  board.readFromStdin();
  board.print();

  return 0;
}
