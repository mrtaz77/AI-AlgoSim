#include <iostream>
#include "./util/util.hpp"
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

	cout << "Valid grid size: " << grid_size << endl;
	
	return 0;
}