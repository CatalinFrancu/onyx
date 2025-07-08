#pragma once

#include "Board.h"
#include "Constants.h"
#include "MCTSScore.h"
#include "Move.h"
#include "MonteCarloTreeNode.h"

class MCTSAgent {
public:
  MCTSAgent(Board& board, int timeLimitMillis);
  Move getBestMove();

private:
  int timeLimitMillis;
  Board rootBoard;
  MonteCarloTreeNode* root;

  // current node and board
  Board board;
  MonteCarloTreeNode* node;

  // reusable buffer for move generation
  Move moveBuf[MAX_MOVES];

  void select();
  void expand();
  MCTSScore simulate();
  void backpropagate(MCTSScore reward);
};
