#include "NPuzzle.hpp"

int NPuzzle::get_number_of_blocks() {
	return grid_size * grid_size;
}

NPuzzle::NPuzzle(int grid_size) {
	this->grid_size = grid_size;
}

void NPuzzle::add_label(int label) {
	grid.push_back(label);
	if(label < get_number_of_blocks()) inversion_util.push_back(label);
}

int NPuzzle::number_of_inversions(int start, int end) {
    if (start == end) return 0;
    int mid = (start + end) / 2;
    int left_inversion_count = number_of_inversions(start, mid);
    int right_inversion_count = number_of_inversions(mid + 1, end);
    int merged_inversion_count = merge_number_of_inversions(start, mid, end);
    return left_inversion_count + right_inversion_count + merged_inversion_count;
}

int NPuzzle::merge_number_of_inversions(int start, int mid, int end) {
    int left_start = start;
    int right_start = mid + 1;
    int count = 0;
    vector<int> temp(end - start + 1);
    int index = 0;
    while (left_start <= mid && right_start <= end) {
        if (inversion_util[left_start] <= inversion_util[right_start]) {
            temp[index++] = inversion_util[left_start++];
        } else {
            temp[index++] = inversion_util[right_start++];
            count += (mid - left_start + 1);
        }
    }
    while (left_start <= mid) temp[index++] = inversion_util[left_start++];
    while (right_start <= end) temp[index++] = inversion_util[right_start++];
    for (size_t i = 0; i < temp.size(); ++i) inversion_util[start + i] = temp[i];
    return count;
}

int NPuzzle::get_row_of_blank_from_bottom() {
	int blank = get_number_of_blocks();
	for(int i = 0; i < blank; i++) {
		if(grid[blank - i - 1] == blank) return (i / grid_size) + 1;
	}
	return -1;
}

int NPuzzle::get_inversion_count() {
	int inversion_count = number_of_inversions(0, get_number_of_blocks() - 2);
	refresh_inversion_util();
	return inversion_count;
}

void NPuzzle::set_solvability_strategy() {
	if(grid_size % 2) solvability = new OddSolvable();
	else solvability = new EvenSolvable();
}

bool NPuzzle::is_solvable() {
	set_solvability_strategy();
	return solvability->is_solvable(get_row_of_blank_from_bottom(), get_inversion_count());
}

void NPuzzle::refresh_inversion_util() {
	inversion_util.clear();
	int blank = get_number_of_blocks();
	for(int i = 0; i < blank; i++) {
		if(grid[i] != blank) inversion_util.push_back(grid[i]);
	}
}

void NPuzzle::solve() {
	root_solver = get_heuristic_based_solver(grid_size, grid, nullptr);
	root_solver->set_heuristic_cost();
	priority_queue<Solver*, vector<Solver*>, Solver::CompareSolver> queue;
	unordered_set<string> closed_list;
	queue.push(root_solver);

	while(!queue.empty()) {
		auto current_solver = queue.top();
		queue.pop();
		if(!current_solver->get_heuristic_cost()) {
			cout << current_solver << endl;
			break;
		}
		
	}
}

void NPuzzle::set_heuristic(string heuristic) { this->heuristic = heuristic; }

Solver* NPuzzle::get_heuristic_based_solver(int grid_size, const vector<int>& grid, Solver* parent) {
	if(heuristic == "hamming") return new HammingSolver(grid_size, grid, parent);
	else if(heuristic == "manhattan") return new ManhattanSolver(grid_size, grid, parent);
}