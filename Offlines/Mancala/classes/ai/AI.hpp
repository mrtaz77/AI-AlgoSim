#pragma once

#include "../heuristics/Heuristic.hpp"
using namespace std;

class AI {
    Heuristic* heuristic;
    int depth;
    bool playerTurn;
public:
    AI(Heuristic* heuristic = nullptr, int depth = 0);
    int decide_move(unique_ptr<GameSnapshot>);
    int minimax(unique_ptr<GameSnapshot>, int, int, int, bool);
};