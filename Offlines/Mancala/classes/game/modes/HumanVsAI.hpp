#pragma once

#include "Mode.hpp"
#include "../../util/util.hpp"
#include "../../ai/AI.hpp"
using namespace std;

class HumanVsAI : public Mode {
    AI ai;
public:
    HumanVsAI();
    void prompt_player_turn(GameSnapshot*) override;
    int get_player_move(GameSnapshot*) override;
};