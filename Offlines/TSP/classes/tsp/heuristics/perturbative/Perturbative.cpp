#include "Perturbative.hpp"

Perturbative::Perturbative(Graph& graph) : Heuristic(graph) {}

void Perturbative::set_tour(vector<int>& tour) { this->tour = tour; }

void Perturbative::set_cost(long double tour_cost) { this->tour_cost = tour_cost; }