#include "./CompareSolver.hpp"

bool CompareSolver::operator()(Solver *lhs, Solver *rhs) {
	if (lhs->get_total_cost() == rhs->get_total_cost()) {
		return lhs->get_heuristic_cost() > rhs->get_heuristic_cost();
	}
	return lhs->get_total_cost() > rhs->get_total_cost();
}