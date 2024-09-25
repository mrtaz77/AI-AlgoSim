#pragma once

#include "../game/GameSnapshot.hpp"

enum Heuristics {
    H1, H2, H3, H4, INVALID
};

class Heuristic {
public:
    virtual int evaluate(GameSnapshot*) = 0;
};