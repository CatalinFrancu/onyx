#include "MCTSAgent.h"

#include "Globals.h"
#include "Log.h"
#include "MoveGen.h"
#include "Util.h"

MCTSAgent::MCTSAgent(Board& board, int timeLimitMillis) {
  this->rootBoard = board;
  this->timeLimitMillis = timeLimitMillis;
  this->root = new MonteCarloTreeNode(NULL);
}

Move MCTSAgent::getBestMove() {
  Util::markTime();
  while (Util::getElapsedTimeMillis() < timeLimitMillis) {
    select();
    expand();
    MCTSScore reward = simulate();
    backpropagate(reward);
  }

  int p = rootBoard.currPlayer;
  MonteCarloTreeNode* child = root->getChildWithBestRatio(p);
  fprintf(stderr, "kibitz Ran %d simulations. Win probability %.3lf.\n",
          this->root->numSimulations,
          child->getWinProbability(p));

  MonteCarloTreeNode* heavy = root->getHeaviestChild();
  if (heavy != child) {
    fprintf(stderr, "kibitz Chose a child with %d simulations; heaviest child has %d.\n",
            child->numSimulations,
            heavy->numSimulations);
  }

  return child->move;
}

void MCTSAgent::select() {
  node = root;
  board = rootBoard;

  while (node->numChildren) {
    node = node->uctSelectChild(board.currPlayer);
    board.makeMove(node->move);
  }
}

void MCTSAgent::expand() {
  if ((node->numSimulations) && !board.isGameOver()) {
    node->expand(&board, moveBuf);
    node = node->selectRandomChild();
    board.makeMove(node->move);
  }
}

MCTSScore MCTSAgent::simulate() {
  MCTSScore reward;
  for (int i = 0; i < MCTS_ROLLOUTS_PER_NODE; i++) {
    Board b = board;
    int turn = 0;
    while ((turn < MCTS_MAX_TURNS) && !b.isGameOver()) {
      turn++;
      MoveGen gen(&b, moveBuf);
      gen.run();
      Move move = gen.getRandomMove();
      b.makeMoveWithReplacement(move);
    }
    // Log::info("Simulation took %d turns", turn);
    reward += b.getMCTSScore();
  }
  return reward;
}

void MCTSAgent::backpropagate(MCTSScore reward) {
  while (node) {
    node->numSimulations += MCTS_ROLLOUTS_PER_NODE;
    node->score += reward;
    node = node->parent;
  }
}
