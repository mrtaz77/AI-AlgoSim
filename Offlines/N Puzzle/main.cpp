#include <iostream>
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
		} else {
			puzzle.add_label(label_no);
		}
	}
	cout << "Valid grid" << endl;
	cout << "Number of Inversions : " << puzzle.get_inversion_count() << endl;
	cout << "Row of blank from bottom : " << puzzle.get_row_of_blank_from_bottom() << endl;
	bool is_solvable = puzzle.is_solvable();
	cout << "Solvable: " << boolalpha << is_solvable << endl;

	if(is_solvable) {
		cout << "Manhattan Heuristic:\n" ;
		puzzle.set_heuristic("manhattan");
		puzzle.solve();
		cout << "\n================================================================\n\n";
		cout << "Hamming Heuristic:\n" ;
		puzzle.set_heuristic("hamming");
		puzzle.solve();
	}

	return 0;
}