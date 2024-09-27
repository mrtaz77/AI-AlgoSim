#pragma once

#include "Modes.hpp"
#include "../GameSnapshot.hpp"
#include "../../heuristics/HeuristicFactory.hpp"
#include "../../heuristics/Heuristic.hpp"
#include "../../heuristics/Heuristics.hpp"
#include "../../util/util.hpp"

using namespace std;

class Mode {
public:
    Mode();
    virtual ~Mode() = default;
    virtual void prompt_player_turn(GameSnapshot*) = 0;
    virtual int get_player_move(GameSnapshot*) = 0;
    static void keyboard_interrupt(int);
    Heuristic* prompt_heuristics();
    int prompt_depth();
};