#pragma once

#include <bits/stdc++.h>
#include "../util/util.hpp"

class GameSnapshot;

using namespace std;

class Turn {
public:
    virtual ~Turn() = default;
    virtual bool is_valid_turn(GameSnapshot&, int) = 0;
    virtual void make_move(GameSnapshot&, int) = 0;
    virtual vector<int> get_valid_moves(GameSnapshot&) = 0;
    virtual unique_ptr<Turn> clone() = 0;
};