#pragma once

#include "Mode.hpp"
#include "../../util/util.hpp"
#include "../../ai/AI.hpp"
using namespace std;

class AIVsAI : public Mode {
    AI playerA;
    AI playerB;
public:
    AIVsAI();
    void prompt_player_turn(GameSnapshot*) override;
    int get_player_move(GameSnapshot*) override;
};