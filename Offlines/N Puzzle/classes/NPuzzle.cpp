#include "NPuzzle.hpp"

int NPuzzle::get_number_of_blocks() {
	return grid_size * grid_size;
}

NPuzzle::NPuzzle(int grid_size) {
	this->grid_size = grid_size;
	this->grid.assign(get_number_of_blocks(), 0);
}

void NPuzzle::add_label(int label) {
	grid.push_back(label);
}