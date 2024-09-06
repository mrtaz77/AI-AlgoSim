#pragma once

#include "./Solver.hpp"

struct CompareSolver {
	bool operator()(Solver *, Solver *);
};