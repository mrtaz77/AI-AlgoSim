#pragma once

#define NUM_OF_BINS_PER_SIDE 6
#define NUM_OF_PLAYERS 2
#define TOTAL_NUM_OF_BINS (NUM_OF_BINS_PER_SIDE * NUM_OF_PLAYERS)
#define NUM_OF_STORAGE NUM_OF_PLAYERS
#define BOARD_SIZE (TOTAL_NUM_OF_BINS + NUM_OF_STORAGE)
#define INITIAL_NUM_OF_STONES_PER_BIN 4

#include <string>
#include "../game/modes/Modes.hpp"
#include "../heuristics/Heuristics.hpp"
using namespace std;

int validate_move(string);
Modes validate_mode_choice(string);
Heuristics validate_heuristic_choice(string);