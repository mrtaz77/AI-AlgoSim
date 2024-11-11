#include "FarthestInsertion.hpp"

FarthestInsertion::FarthestInsertion(Graph& graph) : Constructive(graph), minimum_distances_to_tour(graph.get_number_of_vertices(), numeric_limits<long double>::max()) {}

const string FarthestInsertion::get_heuristic_name() const { return "Farthest Insertion"; }

void FarthestInsertion::solve() {
    auto start = chrono::high_resolution_clock::now();

    size_t num_vertices = g.get_number_of_vertices();
    tour.clear();
    tour.reserve(num_vertices + 1);
    vector<bool> visited(num_vertices, false);

    auto [node1, node2] = find_nodes_farthest_apart();
    tour.push_back(node1); tour.push_back(node2);
    visited[node1] = visited[node2] = true;

    initialize_distances_to_tour(node1, node2);

    while (tour.size() < num_vertices) {
        vector<pair<int, long double>> candidates;

        for (size_t i = 0; i < num_vertices; i++) {
            if (visited[i]) continue;
            candidates.push_back({i, minimum_distances_to_tour[i]});
        }

        sort(candidates.begin(), candidates.end(), [](const pair<int, long double>& a, const pair<int, long double>& b) {
            return a.second > b.second;
        });

        int farthest_node = select_from_candidates(candidates);
        
        int best_position = 0;
        long double best_increment = numeric_limits<long double>::max();
        for(size_t j = 0; j < tour.size(); j++) {
            int next_city = tour[(j + 1) % tour.size()];
            long double increment = g.get_edge_weight(tour[j], farthest_node) +
                                    g.get_edge_weight(farthest_node, next_city) -
                                    g.get_edge_weight(tour[j], next_city);
            if (increment < best_increment) {
                best_increment = increment;
                best_position = j + 1;
            }
        }
        
        tour.insert(tour.begin() + best_position, farthest_node);
        visited[farthest_node] = true;
        
        for (size_t i = 0; i < num_vertices; ++i) {
            if (!visited[i]) {
                minimum_distances_to_tour[i] = min(minimum_distances_to_tour[i], g.get_edge_weight(i, farthest_node));
            }
        }
    }

    tour.push_back(tour[0]);

    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();

    compute_tour_cost();
}

pair<int, int> FarthestInsertion::find_nodes_farthest_apart() {
    int num_vertices = g.get_number_of_vertices();
    long double farthest_distance = -1;
    pair<int, int> farthest_nodes;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            long double distance = g.get_edge_weight(i, j);
            if (distance > farthest_distance) {
                farthest_distance = distance;
                farthest_nodes = {i, j};
            }
        }
    }
    return farthest_nodes;
}

void FarthestInsertion::initialize_distances_to_tour(int node1, int node2) {
    for (int i = 0; i < g.get_number_of_vertices(); ++i) {
        if (i == node1 || i == node2) continue;    
        minimum_distances_to_tour[i] = min(g.get_edge_weight(i, node1), g.get_edge_weight(i, node2));
    }
}

void FarthestInsertion::compute_tour_cost() {
    tour_cost = 0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        tour_cost += g.get_edge_weight(tour[i], tour[i + 1]);
    }
}

bool FarthestInsertion::is_start_variable() { return false; }