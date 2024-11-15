#include "TSP.hpp"

TSP::TSP(Graph& g) : graph(g) {};

void TSP::set_heuristics(Heuristics constructive_heuristic, Heuristics perturbative_heuristic) {
    switch (constructive_heuristic) {
        case Heuristics::NEAREST_NEIGHBOUR:
            this->constructive_heuristic = make_unique<NearestNeighbour>(graph);
            break;
        case Heuristics::FARTHEST_INSERTION:
            this->constructive_heuristic = make_unique<FarthestInsertion>(graph);
            break;
        case Heuristics::MINIMUM_SPANNING_TREE:
            this->constructive_heuristic = make_unique<MST>(graph);
            break;
        default:
            cerr << "Error: Unsupported heuristic type.\n";
            this->constructive_heuristic.reset();
            break;
    }

    switch (perturbative_heuristic) {
        case Heuristics::TWO_OPT:
            this->perturbative_heuristic = make_unique<TwoOpt>(graph);
            break;
        case Heuristics::NODE_SHIFT:
            this->perturbative_heuristic = make_unique<NodeShift>(graph);
            break;
        case Heuristics::TWO_HALF_OPT:
            this->perturbative_heuristic = make_unique<TwoHalfOpt>(graph);
            break;
        default:    
            break;
    }
}

void TSP::run() {
    vector<pair<long double, vector<int>>> tours(graph.get_number_of_vertices(), {0.0, vector<int>(graph.get_number_of_vertices(), 0)});
    int number_of_iterations = (constructive_heuristic->is_start_variable()) ? graph.get_number_of_vertices() : 1;
    if (constructive_heuristic) {
        tour_avg_costs.first = tour_avg_times.first = 0;
        tour_min_costs.first = tour_min_times.first = numeric_limits<long double>::max();
        tour_max_costs.first = tour_max_times.first = numeric_limits<long double>::min();
        for(int i = 0; i < number_of_iterations; ++i) {
            constructive_heuristic->set_starting_node(i);
            constructive_heuristic->solve();
            tours[i].first = constructive_heuristic->get_tour_cost();
            tours[i].second = constructive_heuristic->get_tour();
            tour_avg_costs.first += tours[i].first;
            tour_min_costs.first = min(tour_min_costs.first, tours[i].first);
            tour_max_costs.first = max(tour_max_costs.first, tours[i].first);
            long double tour_time = constructive_heuristic->get_time_taken();
            tour_avg_times.first += tour_time;
            tour_min_times.first = min(tour_min_times.first, tour_time);
            tour_max_times.first = max(tour_max_times.first, tour_time);
        }
        tour_avg_costs.first /= number_of_iterations;
        tour_avg_times.first /= number_of_iterations;
    } else cerr << "Error: No constructive heuristic set. Please set a constructive heuristic before running.\n";
    if(perturbative_heuristic) {
        tour_avg_costs.second = tour_avg_times.second = 0;
        tour_min_costs.second = tour_min_times.second = numeric_limits<long double>::max();
        tour_max_costs.second = tour_max_times.second = numeric_limits<long double>::min();
        for(int i = 0; i < number_of_iterations; ++i) {
            perturbative_heuristic->set_tour(tours[i].second);
            perturbative_heuristic->set_cost(tours[i].first);
            perturbative_heuristic->solve();
            tours[i].first = perturbative_heuristic->get_tour_cost();
            tour_avg_costs.second += tours[i].first;
            tour_min_costs.second = min(tour_min_costs.second, tours[i].first);
            tour_max_costs.second = max(tour_max_costs.second, tours[i].first);
            long double tour_time = perturbative_heuristic->get_time_taken();
            tour_avg_times.second += tour_time;
            tour_min_times.second = min(tour_min_times.second, tour_time);
            tour_max_times.second = max(tour_max_times.second, tour_time);
        }
        tour_avg_costs.second /= number_of_iterations;
        tour_avg_times.second /= number_of_iterations;
    } else cerr << "Error: No perturbative heuristic set. Please set a perturbative heuristic before running.\n";
}

void TSP::set_graph(Graph& graph) {
    this->graph = graph;
}

void TSP::set_version(Versions version) { this->constructive_heuristic->set_version(version); }

const string TSP::get_heuristic_name(Heuristics heuristic) const { return (heuristic == Heuristics::PERTURBATIVE) ? perturbative_heuristic->get_heuristic_name() : constructive_heuristic->get_heuristic_name(); }

long double TSP::get_avg_cost(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_avg_costs.first : tour_avg_costs.second; }

long double TSP::get_worst_cost(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_max_costs.first : tour_max_costs.second; }

long double TSP::get_best_cost(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_min_costs.first : tour_min_costs.second; }

const Graph& TSP::get_graph() const { return graph; }

Versions TSP::get_version() const { return constructive_heuristic->get_version(); }

long double TSP::get_avg_time(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_avg_times.first : tour_avg_times.second; }

long double TSP::get_worst_time(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_max_times.first : tour_max_times.second; }

long double TSP::get_best_time(Heuristics heuristic) const { return (heuristic == Heuristics::CONSTRUCTIVE) ? tour_min_times.first : tour_min_times.second; }
