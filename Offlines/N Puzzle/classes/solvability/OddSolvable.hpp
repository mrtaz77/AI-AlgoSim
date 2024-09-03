#pragma once
#include "./Solvable.hpp"

class OddSolvable : public Solvable {
	public:
	bool is_solvable(int, int) override;
};