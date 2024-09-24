#pragma once
#include "Turn.hpp"

class PlayerATurn : public Turn {
public:
    void makeMove(GameSnapshot&, int) override;
};