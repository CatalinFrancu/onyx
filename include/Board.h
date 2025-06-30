#pragma once

#include "ChipSet.h"
#include "Move.h"
#include "Player.h"
#include "Score.h"
#include <vector>

class Board {
public:
  int currPlayer;
  ChipSet chips;
  std::vector<char> cards; // high-level cards go first
  std::vector<char> nobles;
  std::vector<Player> players;

  void readFromStdin();
  void makeMove(Move& m);
  void undoMove(Move& m);
  Score staticEval();

  // Translate a move into a list of tokens according to the protocol.
  std::vector<int> translateMove(Move m);
  void print();

private:
  void readCards();
  void readNobles();

  std::vector<int> translateTakeDifferentMove(Move m);
  std::vector<int> translateTakeSameMove(Move m);
  std::vector<int> translateReserveMove(Move m);
  std::vector<int> translateBuyFaceupMove(Move m);
  std::vector<int> translateBuyReserveMove(Move m);
  void translateReturns(Move m, std::vector<int>& v);
};
