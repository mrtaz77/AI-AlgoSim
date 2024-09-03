#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "./solvability/Solvable.hpp"
#include "./solvability/EvenSolvable.hpp"
#include "./solvability/OddSolvable.hpp"
using namespace std;

class NPuzzle {
	int grid_size;
	vector<int> grid;
	vector<int> inversion_util;
	Solvable* solvability;
	int number_of_inversions(int, int);
	int merge_number_of_inversions(int, int, int);
	public:
	NPuzzle(int);
	int get_number_of_blocks ();
	void add_label(int);
	int get_inversion_count();
	int get_row_of_blank_from_bottom();
};