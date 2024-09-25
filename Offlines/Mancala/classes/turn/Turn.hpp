#pragma once

class GameSnapshot;

#include "../constants/Constants.hpp"

class Turn {
public:
    virtual ~Turn() = default;
    virtual bool is_valid_turn(GameSnapshot&, int) = 0;
    virtual void make_move(GameSnapshot&, int) = 0;
    virtual vector<int> get_valid_moves(GameSnapshot&) = 0;
};