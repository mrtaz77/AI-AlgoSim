#include "TSP.hpp"

TSP::TSP(Graph& g) : g(g) {};

void TSP::set_heuristic(Heuristics heuristicType) {
    switch (heuristicType) {
        case Heuristics::NEAREST_NEIGHBOUR:
            heuristic = make_unique<NearestNeighbour>(g);
            break;

        default:
            cerr << "Error: Unsupported heuristic type.\n";
            heuristic.reset();
            break;
    }
}

void TSP::run() {
    if (heuristic) {
        heuristic->solve();
    } else {
        cerr << "Error: No heuristic set. Please set a heuristic before running.\n";
    }
}

void TSP::set_graph(Graph& graph) {
    this->g = graph;
}

string TSP::get_heuristic_name() const {
    if (dynamic_cast<NearestNeighbour*>(heuristic.get())) return "Nearest Neighbour";
    return "Unknown Heuristic";
}

vector<int>& TSP::get_tour() { return heuristic->get_tour(); }

long double TSP::get_cost() const { return heuristic->get_tour_cost(); }

long double TSP::get_time() const { return heuristic->get_time_taken(); }