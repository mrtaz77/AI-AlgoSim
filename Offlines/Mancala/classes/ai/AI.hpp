#pragma once

#include "../heuristics/Heuristic.hpp"
#include "../heuristics/HeuristicFactory.hpp"
#include "../util/util.hpp"
using namespace std;

class AI {
    Heuristic* heuristic;
    int depth;
    bool playerTurn;
public:
    AI();
    int decide_move(unique_ptr<GameSnapshot>);
    int minimax(unique_ptr<GameSnapshot>, int, int, int, bool);
};