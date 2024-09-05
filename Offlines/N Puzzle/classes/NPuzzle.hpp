#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "./solvability/Solvable.hpp"
#include "./solvability/EvenSolvable.hpp"
#include "./solvability/OddSolvable.hpp"
#include "./solver/Solver.hpp"
#include "./solver/HammingSolver.hpp"
#include "./solver/ManhattanSolver.hpp"
#include <string>
using namespace std;

class NPuzzle {
	int grid_size;
	vector<int> grid;
	vector<int> inversion_util;
	Solvable* solvability;
	Solver* root_solver;
	int number_of_inversions(int, int);
	int merge_number_of_inversions(int, int, int);
	void set_solvability_strategy();
	void refresh_inversion_util();
public:
	NPuzzle(int);
	int get_number_of_blocks ();
	void add_label(int);
	int get_inversion_count();
	int get_row_of_blank_from_bottom();
	bool is_solvable();
	void set_solver(string);
	void solve();
};