#pragma once
#include "../game/GameSnapshot.hpp"
#include "Heuristic.hpp"

using namespace std;

class H4 : public Heuristic {
	int W1, W2, W3, W4;
public:
	H4(int, int, int, int);
	int evaluate(GameSnapshot*) override;
};
