#pragma once

#include "../game/GameSnapshot.hpp"

class Heuristic {
public:
    virtual int evaluate(GameSnapshot*) = 0;
};