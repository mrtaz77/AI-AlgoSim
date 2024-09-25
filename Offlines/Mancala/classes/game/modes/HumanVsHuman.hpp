#pragma once

#include "Mode.hpp"
#include "../../util/util.hpp"
using namespace std;

class HumanVsHuman : public Mode {
public:
    void prompt_player_turn(GameSnapshot*) override;
    int get_player_move() override;
};