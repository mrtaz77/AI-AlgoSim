#include "NodeShift.hpp"

NodeShift::NodeShift(Graph& graph) : Perturbative(graph) {}

const string NodeShift::get_heuristic_name() const { return "NodeShift"; }

long double NodeShift::calculate_improvement(int x0_predecessor, int x0, int x0_successor, int y1, int y2) {
    auto prev_length = g.get_edge_weight(x0_predecessor, x0) 
    + g.get_edge_weight(x0, x0_successor) + g.get_edge_weight(y1, y2);
    auto new_length = g.get_edge_weight(x0_predecessor, x0_successor)
    + g.get_edge_weight(y1, x0) + g.get_edge_weight(x0, y2);
    return prev_length - new_length;
}


/* 
Shifts the city tour[i] from its current position to position
after current city tour[j], i.e. between cities tour[j] and tour[j+1]. 
*/
void NodeShift::apply_change(int i, int j) {
    auto shift_size = (j - i + 1 + g.get_number_of_vertices()) % g.get_number_of_vertices();
    auto x0 = tour[i];
    auto left = i;
    auto right = 0;
    for (int k = 1; k <= shift_size; k++) {
        right = (left + 1) % g.get_number_of_vertices();
        tour[left] = tour[right];
        left = right;
    }
    tour[j] = x0;
}

void NodeShift::solve() {
    auto start = chrono::high_resolution_clock::now();
    auto locally_optimal = false;
    int i, j, x0_predecessor, x0, x0_successor, y1, y2;
    while(!locally_optimal) {
        locally_optimal = true;
        for(int k = 0; k < g.get_number_of_vertices(); k++) {
            i = k;
            x0_predecessor = tour[(i - 1 + g.get_number_of_vertices()) % g.get_number_of_vertices()];
            x0 = tour[i];
            x0_successor = tour[(i + 1) % g.get_number_of_vertices()];
            for(int l = 1; l < g.get_number_of_vertices() - 1; l++) {
                j = (i + l) % g.get_number_of_vertices();
                y1 = tour[j];
                y2 = tour[(j + 1) % g.get_number_of_vertices()];
                auto improvement = calculate_improvement(x0_predecessor, x0, x0_successor, y1, y2);
                if(improvement > THRESHOLD) {
                    apply_change(i, j);
                    tour_cost -= improvement;
                    locally_optimal = false;
                    break;
                }
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();
}