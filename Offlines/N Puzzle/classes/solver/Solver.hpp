#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Solver {
	int actual_cost;
	int heuristic_cost;
	int parent_blank_idx;
	int grid_size;
	vector<int> grid;
	vector<Solver*> children;
	public:
	Solver(int, const vector<int>&);
	// virtual int get_heuristic_cost() = 0;
	friend ostream& operator<<(ostream&, const Solver&);
};