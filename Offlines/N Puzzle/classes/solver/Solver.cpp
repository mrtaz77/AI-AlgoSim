#include "./Solver.hpp"

Solver::Solver(int grid_size, const vector<int>& grid, Solver* parent = nullptr) :
	actual_cost(0),
	grid_size(grid_size),
	heuristic_cost(0),
	grid(grid),
	parent(parent) {
	set_blank_idx();
	set_hash();
}

ostream& operator<<(ostream& out, const Solver& solver) {
    int blank_label = solver.grid.size();
    int width = to_string(blank_label).size(); // width needed for the largest number
    int line_length = solver.grid_size * (width + 3) + 1; // length of the border line

    out << string(line_length, '-') << endl;

    for (size_t i = 0; i < solver.grid.size(); ++i) {
        out << "| ";
        if (solver.grid[i] == blank_label) out << setw(width) << "*";
        else out << setw(width) << solver.grid[i];
        out << " ";
        if ((i + 1) % solver.grid_size == 0)
            out << "|\n" << string(line_length, '-') << endl;
    }
    out << "Actual Cost: " << solver.actual_cost << "\nHeuristic Cost: " << solver.heuristic_cost << endl;
    return out;
}

int Solver::get_heuristic_cost() const { return heuristic_cost; }

Solver::~Solver() {
	delete parent;
}

void Solver::set_parent(Solver* parent) { this->parent = parent; }

Solver* Solver::get_parent() const { return parent; }

void Solver::increment_actual_cost() { actual_cost++; }

int Solver::get_actual_cost() const { return actual_cost; }

int Solver::get_total_cost() const { return actual_cost + heuristic_cost; }

void Solver::set_hash() {
	stringstream ss;
    for (int label : grid) ss << label;
    hash = ss.str();
}

string Solver::get_hash() const { return hash; }

bool Solver::operator==(const Solver& other) const { return this->hash == other.hash; }

void Solver::set_blank_idx() {
	int blank = grid.size();
	auto it = find(grid.begin(), grid.end(), blank);
	blank_idx = distance(grid.begin(), it);
}