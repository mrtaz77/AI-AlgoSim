#pragma once

#include "Mode.hpp"
#include "../../util/util.hpp"
#include "../../ai/AI.hpp"
using namespace std;

class AIVsHuman : public Mode {
    AI ai;
public:
    AIVsHuman();
    void prompt_player_turn(GameSnapshot*) override;
    int get_player_move(GameSnapshot*) override;
};