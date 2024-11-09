#include "TSP.hpp"

TSP::TSP(Graph& g) : g(g) {};

void TSP::set_heuristic(Heuristics heuristicType) {
    switch (heuristicType) {
        case Heuristics::NEAREST_NEIGHBOUR:
            constructive_heuristic = make_unique<NearestNeighbour>(g);
            break;

        default:
            cerr << "Error: Unsupported heuristic type.\n";
            constructive_heuristic.reset();
            break;
    }
}

void TSP::run() {
    if (constructive_heuristic) {
        constructive_heuristic->solve();
    } else {
        cerr << "Error: No heuristic set. Please set a heuristic before running.\n";
    }
}

void TSP::set_graph(Graph& graph) {
    this->g = graph;
}

string TSP::get_heuristic_name() const {
    if (dynamic_cast<NearestNeighbour*>(constructive_heuristic.get())) return "Nearest Neighbour";
    return "Unknown Heuristic";
}

vector<int>& TSP::get_tour() { return constructive_heuristic->get_tour(); }

long double TSP::get_cost() const { return constructive_heuristic->get_tour_cost(); }

long double TSP::get_time() const { return constructive_heuristic->get_time_taken(); }

void TSP::set_version(Versions version) {
    this->constructive_heuristic->set_version(version);
}