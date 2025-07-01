#pragma once

#include "BitSet.h"
#include "ChipSet.h"
#include "Move.h"
#include "Player.h"
#include "Score.h"
#include <vector>

class Board {
public:
  int numPlayers;
  int currPlayer;
  ChipSet chips;
  BitSet cards;
  std::vector<char> nobles;
  Player players[MAX_PLAYERS];

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
  std::vector<int> translateBuyMove(Move m);

  void printCards();
};
