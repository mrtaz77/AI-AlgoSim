#pragma once
#include "../game/GameSnapshot.hpp"
#include "Heuristic.hpp"

using namespace std;

class H2 : public Heuristic {
	int W1, W2;
public:
	H2(int, int);
	int evaluate(GameSnapshot*) override;
};
