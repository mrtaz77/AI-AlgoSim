#pragma once
#include <iostream>
#include <vector>
using namespace std;

class NPuzzle {
	int grid_size;
	vector<int> grid;
	vector<int> inversion_util;
	int number_of_inversions(int, int);
	int merge_number_of_inversions(int, int, int);
	public:
	NPuzzle(int);
	int get_number_of_blocks ();
	void add_label(int);
	int get_inversion_count();
};