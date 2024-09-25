#pragma once
#include "../game/GameSnapshot.hpp"
#include "Heuristic.hpp"

using namespace std;

class H1 : public Heuristic {
public:
	int evaluate(GameSnapshot*) override;
};
