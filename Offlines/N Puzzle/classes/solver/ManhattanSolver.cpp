#include "./ManhattanSolver.hpp"

ManhattanSolver::ManhattanSolver(int grid_size, const vector<int>& grid)
    : Solver(grid_size, grid) {}

void ManhattanSolver::set_heuristic_cost() {
	int blank = grid.size();
	for(int i = 0; i < blank ; i++) {
		if(!(grid[i] == blank ||  i == grid[i] - 1)) {
			int actual_idx = grid[i] - 1;
			int actual_row = actual_idx / grid_size;
			int actual_col = actual_idx % grid_size;
			int current_idx = i;
			int current_row = current_idx / grid_size;
			int current_col = current_idx % grid_size;
			int row_distance = abs(current_row - actual_row);
			int col_distance = abs(current_col - actual_col);
			heuristic_cost += (row_distance + col_distance);
		}
	}
}