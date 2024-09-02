#pragma once
#include <iostream>
#include <vector>
using namespace std;

class NPuzzle {
	int grid_size;
	vector<int> grid;
	public:
	NPuzzle(int);
	int get_number_of_blocks ();
	void add_label(int);
};