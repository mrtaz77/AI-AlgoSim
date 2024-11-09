#include "heuristic.hpp"

Heuristic::Heuristic(Graph& graph)
: g(graph), tour_cost(0.0), time_taken(0.0) {}

vector<int>& Heuristic::get_tour() {
    return tour;
}

long double Heuristic::get_time_taken() const {
    return time_taken;
}

long double Heuristic::get_tour_cost() const {
    return tour_cost;
}

