#pragma once

#include "Turn.hpp"
#include "../game/GameSnapshot.hpp"
#include "PlayerATurn.hpp"

class PlayerBTurn : public Turn {
public:
    bool is_valid_turn(GameSnapshot&, int) override;
    void make_move(GameSnapshot&, int, bool) override;
    vector<int> get_valid_moves(GameSnapshot&) override;
    unique_ptr<Turn> clone() const override;
};