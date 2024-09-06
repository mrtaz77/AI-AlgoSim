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
#include "./solver/CompareSolver.hpp"
#include <string>
#include <queue>
#include <functional>
#include <unordered_set>
using namespace std;

class NPuzzle {
	int grid_size;
	vector<int> grid;
	vector<int> inversion_util;
	Solvable* solvability;
	Solver* root_solver;
	string heuristic;
	int number_of_inversions(int, int);
	int merge_number_of_inversions(int, int, int);
	void set_solvability_strategy();
	void refresh_inversion_util();
	Solver* get_heuristic_based_solver(const vector<int>&, Solver*);
	vector<Solver*> get_neighbors(Solver*);
public:
	NPuzzle(int);
	int get_number_of_blocks ();
	void add_label(int);
	int get_inversion_count();
	int get_row_of_blank_from_bottom();
	bool is_solvable();
	void solve();
	void set_heuristic(string);
	void print_solution_steps(Solver*);
};