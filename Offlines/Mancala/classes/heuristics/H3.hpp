#pragma once
#include "../game/GameSnapshot.hpp"
#include "Heuristic.hpp"

using namespace std;

class H3 : public Heuristic {
	int W1, W2, W3;
public:
	H3(int, int, int);
	int evaluate(GameSnapshot*) override;
};
