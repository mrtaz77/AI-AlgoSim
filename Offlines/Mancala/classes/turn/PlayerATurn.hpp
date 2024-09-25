#pragma once

#include "Turn.hpp"
#include "../game/GameSnapshot.hpp"
#include "PlayerBTurn.hpp"

class PlayerATurn : public Turn {
public:
    bool is_valid_turn(GameSnapshot&, int) override;
    void make_move(GameSnapshot&, int) override;
};