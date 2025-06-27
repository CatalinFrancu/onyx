#include "Board.h"
#include "Card.h"

int main(int argc, char** argv) {
  Card::createAll();

  Board board;
  board.readFromStdin();
  board.print();

  return 0;
}
