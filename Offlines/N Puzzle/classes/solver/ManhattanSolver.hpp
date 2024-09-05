#pragma once

#include "./Solver.hpp"
#include <cstdlib>

class ManhattanSolver : public Solver {
	public:
	ManhattanSolver(int, const vector<int>&, Solver*);
	void set_heuristic_cost() override;
};