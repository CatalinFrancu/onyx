#pragma once

/**
 * Use this file for values taht are built into the game rules or the code
 * architecture and that the user should not mess with.
 **/

typedef unsigned __int128 u128;
typedef unsigned long long u64;

const int MAX_PLAYERS = 4;

const int NUM_COLORS = 5;

const int MAX_CHIPS = 10;
const int MAX_TAKE = 3;
const int TAKE_TWO_LIMIT = 4;

const int NUM_CARDS = 90;
const int NUM_CARD_LEVELS = 3;
const int NUM_FACE_UP_CARDS_PER_LEVEL = 4;
const int MAX_ID_PER_LEVEL[NUM_CARD_LEVELS + 1] = { 0, 40, 70, 90 };

const int MAX_RESERVE = 3;

const int NUM_NOBLES = 10;
const int NOBLE_POINTS = 3;

const int ENDGAME_POINTS = 15;

const int M_TAKE_DIFFERENT = 1;
const int M_TAKE_SAME = 2;
const int M_RESERVE = 3;
const int M_BUY_FACEUP = 4;
const int M_BUY_RESERVE = 5;
// Weights for various move types in random rollouts.
const int MCTS_WEIGHTS[6] = { 0, 300, 300, 1, 1000, 1000 };

const int MAX_MOVES = 50;

const int INFIN = 10'000'000;

const int LOG_FATAL = 0;
const int LOG_ERROR = 1;
const int LOG_WARN = 2;
const int LOG_SUCCESS = 3;
const int LOG_INFO = 4;
const int LOG_DEBUG = 5;

const int STRAT_MINIMAX = 0;
const int STRAT_MCTS = 1;

const int MCTS_ROLLOUTS_PER_NODE = 1;
const int MCTS_EXPLORATION_CONSTANT = 1.41;
const int MCTS_MAX_TURNS = 200;
