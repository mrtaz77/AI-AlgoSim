#pragma once

class GameSnapshot;

#include <bits/stdc++.h>
#include "../constants/Constants.hpp"

using namespace std;

class Turn {
public:
    virtual ~Turn() = default;
    virtual bool is_valid_turn(GameSnapshot&, int) = 0;
    virtual void make_move(GameSnapshot&, int, bool) = 0;
    virtual vector<int> get_valid_moves(GameSnapshot&) = 0;
    virtual unique_ptr<Turn> clone() const = 0;
};