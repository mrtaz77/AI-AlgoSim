#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

class Solver
{
	int step_cost;
	int blank_idx;
	Solver *parent;
	string hash;

protected:
	int grid_size;
	int heuristic_cost;
	vector<int> grid;

public:
	Solver(int, const vector<int> &, Solver *parent = nullptr);
	virtual ~Solver();
	virtual void set_heuristic_cost() = 0;
	int get_heuristic_cost() const;
	friend ostream &operator<<(ostream &, const Solver &);
	void set_parent(Solver *);
	Solver *get_parent() const;
	int get_step_cost() const;
	int get_total_cost() const;
	bool operator==(const Solver &) const;
	void set_hash();
	string get_hash() const;
	void set_blank_idx();
	int get_blank_idx() const;
	vector<int> get_grid() const;
};