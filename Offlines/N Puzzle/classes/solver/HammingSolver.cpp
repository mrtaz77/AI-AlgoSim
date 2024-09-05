#include "./HammingSolver.hpp"

HammingSolver::HammingSolver(int grid_size, const vector<int>& grid, Solver* parent)
    : Solver(grid_size, grid, parent) {}

void HammingSolver::set_heuristic_cost() {
	int blank = grid.size();
	for(int i = 0; i < blank ; i++) {
		if(!(grid[i] == blank ||  i == grid[i] - 1)) heuristic_cost++;
	}
}