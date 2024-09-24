#pragma once
#include "Turn.hpp"

class PlayerBTurn : public Turn {
public:
    void makeMove(GameSnapshot&, int) override;
};