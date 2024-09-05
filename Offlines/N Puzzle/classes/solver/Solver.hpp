#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Solver {
	int actual_cost;
	int parent_blank_idx;
	Solver* parent;
protected:
	int grid_size;
	int heuristic_cost;
	vector<int> grid;
public:
	Solver(int, const vector<int>&, Solver* parent=nullptr);
	virtual ~Solver();
	virtual void set_heuristic_cost() = 0;
	int get_heuristic_cost() const;
	friend ostream& operator<<(ostream&, const Solver&);
	void set_parent(Solver*);
	Solver* get_parent() const;
	void increment_actual_cost();
	int get_actual_cost() const;
	int get_total_cost() const;
	struct CompareSolver {
        bool operator()(Solver* lhs, Solver* rhs) const {
            return lhs->get_total_cost() > rhs->get_total_cost();  // Min-heap based on total cost
        }
    };
};