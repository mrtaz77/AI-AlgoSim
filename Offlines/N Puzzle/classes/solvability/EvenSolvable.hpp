#pragma once
#include "./Solvable.hpp"
#include <iostream>

class EvenSolvable : public Solvable {
	public:
	bool is_solvable(int, int) override;
};