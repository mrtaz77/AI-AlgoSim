#pragma once

#include "../GameSnapshot.hpp"

enum class Modes {
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_AI,
    INVALID
};

class Mode {
public:
    virtual ~Mode() = default;
    virtual void prompt_player_turn(GameSnapshot*) = 0;
    virtual int get_player_move(GameSnapshot*) = 0;
};