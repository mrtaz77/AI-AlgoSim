#include "./EvenSolvable.hpp"

bool EvenSolvable::is_solvable(int row_of_blank_from_bottom, int numberOfInversions) {
	return (row_of_blank_from_bottom % 2 == 0) != (numberOfInversions % 2 == 0);
}