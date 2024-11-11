#include "NearestNeighbour.hpp"

NearestNeighbour::NearestNeighbour(Graph& graph) : Constructive(graph) {}

void NearestNeighbour::solve() {
    auto start = chrono::high_resolution_clock::now();

    int num_vertices = g.get_number_of_vertices();
    tour.clear();
    tour.reserve(num_vertices + 1);
    vector<bool> visited(num_vertices, false);

    int currentNode = starting_node;
    visited[currentNode] = true;
    tour.push_back(currentNode);

    tour_cost = 0.0;

    for (int i = 1; i < num_vertices; ++i) {
        vector<pair<int, long double>> candidates;
        for (int j = 0; j < num_vertices; ++j) {
            if (!visited[j]) {
                long double distance = g.get_edge_weight(currentNode, j);
                candidates.emplace_back(j, distance);
            }
        }

        sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        int nextNode = select_from_candidates(candidates);
        if (nextNode != -1) {
            visited[nextNode] = true;
            tour.push_back(nextNode);
            tour_cost += g.get_edge_weight(currentNode, nextNode);
            currentNode = nextNode;
        } else {
            cerr << "Warning: Could not complete tour, graph might not be fully connected.\n";
            break;
        }
    }

    tour_cost += g.get_edge_weight(currentNode, tour[0]);
    tour.push_back(tour[0]);

    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();
}

const string NearestNeighbour::get_heuristic_name() const { return "Nearest Neighbour"; }

bool NearestNeighbour::is_start_variable() { return true; }
