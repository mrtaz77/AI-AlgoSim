#pragma once

#include "./Solver.hpp"

class HammingSolver : public Solver {
	public:
	HammingSolver(int, const vector<int>&);
	void set_heuristic_cost() override;
};