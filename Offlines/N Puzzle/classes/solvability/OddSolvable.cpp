#include "./OddSolvable.hpp"

bool OddSolvable::is_solvable(int /*row_of_blank_from_bottom*/, int numberOfInversions) {
	return !(numberOfInversions % 2);
}