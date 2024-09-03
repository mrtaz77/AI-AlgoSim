#include "util.hpp"

bool is_valid_grid_size(int grid_size) { return grid_size >= 3; }

bool is_valid_block_number(int label, int num_of_blocks) {
	return label > 0 && label <= num_of_blocks;
}

int convert_block_label_to_number(string label, int num_of_blocks) {
	if(label == "*") return num_of_blocks;
	for (char c : label) {
        if (!isdigit(c)) {
            return -1;
        }
    }
	return stoi(label);
}

int validate_block_label(string label, int num_of_blocks) {
	int label_no = convert_block_label_to_number(label, num_of_blocks);
	if(!is_valid_block_number(label_no, num_of_blocks)) return -1;
	else return label_no;
}