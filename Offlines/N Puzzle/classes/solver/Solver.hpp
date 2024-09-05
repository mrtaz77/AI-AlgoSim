#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Solver {
	int actual_cost;
	int parent_blank_idx;
	int grid_size;
	vector<Solver*> children;
	protected:
	int heuristic_cost;
	vector<int> grid;
	public:
	Solver(int, const vector<int>&);
	virtual void set_heuristic_cost() = 0;
	int get_heuristic_cost() const;
	friend ostream& operator<<(ostream&, const Solver&);
};