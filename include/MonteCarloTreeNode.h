#pragma once

#include "Board.h"
#include "MCTSScore.h"
#include "Move.h"

class MonteCarloTreeNode {
public:
  int numSimulations;
  MCTSScore score;

  MonteCarloTreeNode* parent;
  int numChildren;
  MonteCarloTreeNode* children; // array of children, allocated dynamically

  Move move; // move that got us here from the parent

  MonteCarloTreeNode(MonteCarloTreeNode* parent);

  // Select a child based on the UCT formula.
  MonteCarloTreeNode* uctSelectChild(int currPlayer);

  MonteCarloTreeNode* getChildWithBestRatio(int Currplayer);

  void expand(Board* board, Move* moveBuf);
  MonteCarloTreeNode* selectRandomChild();
};
