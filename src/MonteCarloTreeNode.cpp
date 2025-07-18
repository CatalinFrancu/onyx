#include "MonteCarloTreeNode.h"

#include "Constants.h"
#include "Globals.h"
#include "Log.h"
#include "MoveGen.h"
#include "Util.h"
#include <math.h>

MonteCarloTreeNode::MonteCarloTreeNode(MonteCarloTreeNode* parent) {
  this->parent = parent;
  this->numSimulations = 0;
  this->numChildren = 0;
}

void MonteCarloTreeNode::expand(Board* board, Move* moveBuf) {
  MoveGen gen(board, moveBuf);
  gen.run();
  int size = sizeof(MonteCarloTreeNode);
  this->numChildren = gen.numMoves;
  this->children = (MonteCarloTreeNode*)malloc(size * gen.numMoves);

  for (int i = 0; i < gen.numMoves; i++) {
    children[i] = MonteCarloTreeNode(this);
    children[i].move = gen.moves[i];
  }
}

MonteCarloTreeNode* MonteCarloTreeNode::selectRandomChild() {
  if (!numChildren) {
    Log::fatal("Called selectRandomChild() on unexpanded node!");
  }

  int index = Util::rand(0, numChildren - 1);
  return &this->children[index];
}

MonteCarloTreeNode* MonteCarloTreeNode::uctSelectChild(int currPlayer) {
  double logParent = log(numSimulations);

  double best = -INFINITY;
  int besti = 0;

  for (int i = 0; i < numChildren; i++) {
    MonteCarloTreeNode* c = children + i; // syntactic sugar
    double uct;
    if (!c->numSimulations) {
      uct = INFINITY;
    } else {
      double exploitation = (double)c->score.s[currPlayer] / c->numSimulations;
      double exploration = sqrt(logParent / c->numSimulations);
      uct = exploitation + MCTS_EXPLORATION_CONSTANT * exploration;
    }

    if (uct > best) {
      best = uct;
      besti = i;
    }
  }

  return &children[besti];
}

double MonteCarloTreeNode::getWinProbability(int currPlayer) {
  return numSimulations
    ? score.s[currPlayer] / numSimulations
    : -INFINITY;
}

MonteCarloTreeNode* MonteCarloTreeNode::getChildWithBestRatio(int currPlayer) {
  double best = -INFINITY;
  int besti = 0;

  for (int i = 0; i < numChildren; i++) {
    MonteCarloTreeNode* c = children + i; // syntactic sugar
    double r = c->getWinProbability(currPlayer);

    Log::debug("Child %d move %s has %d simulations, win chance %0.5lf",
               i, c->move.toString().c_str(), c->numSimulations, r);

    if (r > best) {
      best = r;
      besti = i;
    }
  }

  return &children[besti];
}

MonteCarloTreeNode* MonteCarloTreeNode::getHeaviestChild() {
  double best = -INFINITY;
  int besti = 0;

  for (int i = 0; i < numChildren; i++) {
    MonteCarloTreeNode* c = children + i; // syntactic sugar
    if (c->numSimulations > best) {
      best = c->numSimulations;
      besti = i;
    }
  }

  return &children[besti];
}
