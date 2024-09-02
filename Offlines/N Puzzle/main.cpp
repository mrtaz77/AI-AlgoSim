#include <iostream>
#include <vector>
#include "./util/util.hpp"
#include "./classes/NPuzzle.hpp"
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int grid_size;
	cin >> grid_size >> ws;
	
	if(!is_valid_grid_size(grid_size)) {
		cout << "Invalid grid size: " << grid_size << endl;
		return 0;
	}

	NPuzzle puzzle(grid_size);
	int num_of_blocks = puzzle.get_number_of_blocks();
	string label;

	for(int i = 0; i < num_of_blocks; i++) {
		cin >> label;
		int label_no = validate_block_label(label, num_of_blocks);
		if(label_no == -1) {
			cout << "Invalid label: " << label << endl;
			return 0;
		}
	}
	cout << "Valid grid" << endl;
	
	return 0;
}