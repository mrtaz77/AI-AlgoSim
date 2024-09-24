#pragma once
#include "GameSnapshot.hpp"

class Turn {
public:
    virtual ~Turn() = default;
    virtual void makeMove(GameSnapshot&, int) = 0;
};