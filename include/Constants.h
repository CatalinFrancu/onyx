#pragma once

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

const int M_TAKE_DIFFERENT = 1;
const int M_TAKE_SAME = 2;
const int M_RESERVE = 3;
const int M_BUY_FACEUP = 4;
const int M_BUY_RESERVE = 5;

const int MAX_MOVES = 1'000;

const int LOG_FATAL = 0;
const int LOG_ERROR = 1;
const int LOG_WARN = 2;
const int LOG_SUCCESS = 3;
const int LOG_INFO = 4;
const int LOG_DEBUG = 5;

const int LOG_LEVEL = LOG_DEBUG;

const char CHIP_CHAR[5] = "◉";
const char CARD_CHAR[5] = "🂠";
