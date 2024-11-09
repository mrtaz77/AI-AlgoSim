#include "NearestNeighbour.hpp"

void NearestNeighbour::solve() {
    auto start = chrono::high_resolution_clock::now();

    int numVertices = g.get_number_of_vertices();
    tour.clear();
    tour.reserve(numVertices);
    vector<bool> visited(numVertices, false);

    int currentNode = 0;
    visited[currentNode] = true;
    tour.push_back(currentNode);

    tour_cost = 0.0;

    for (int i = 1; i < numVertices; ++i) {
        int nextNode = -1;
        double minDistance = numeric_limits<double>::max();

        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && g.get_edge_weight(currentNode, j) < minDistance) {
                minDistance = g.get_edge_weight(currentNode, j);
                nextNode = j;
            }
        }

        if (nextNode != -1) {
            visited[nextNode] = true;
            tour.push_back(nextNode);
            tour_cost += minDistance;
            currentNode = nextNode;
        }
    }

    tour_cost += g.get_edge_weight(currentNode, tour[0]);
    tour.push_back(tour[0]);

    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();
}