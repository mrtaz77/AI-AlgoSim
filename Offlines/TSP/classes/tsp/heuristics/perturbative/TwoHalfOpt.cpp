#include "TwoHalfOpt.hpp"

TwoHalfOpt::TwoHalfOpt(Graph& graph) : Perturbative(graph) {}

const string TwoHalfOpt::get_heuristic_name() const {
    return "2.5opt";
}

// 2opt move
void TwoHalfOpt::apply_change(int i, int j) {
    int start_index = (i + 1) % g.get_number_of_vertices();
    int end_index = j;
    int inversion_size = ((g.get_number_of_vertices() + end_index - start_index + 1) % g.get_number_of_vertices()) / 2;
    int left = start_index;
    int right = end_index;
    for(int i = 1; i <= inversion_size; i++) {
        swap(tour[left], tour[right]);
        left = (left + 1) % g.get_number_of_vertices();
        right = (g.get_number_of_vertices() + right - 1) % g.get_number_of_vertices();
    }
}

// node shift move
void TwoHalfOpt::node_shift(int i, int j) {
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

// 2opt gain
long double TwoHalfOpt::calculate_improvement(int x1, int x2, int y1, int y2) {
    auto prev_length = g.get_edge_weight(x1, x2) + g.get_edge_weight(y1, y2);
    auto new_length = g.get_edge_weight(x1, y1) + g.get_edge_weight(x2, y2);
    return prev_length - new_length;
}

// node shift gain
long double TwoHalfOpt::calculate_node_shift_improvement(int x0_predecessor, int x0, int x0_successor, int y1, int y2) {
    auto prev_length = g.get_edge_weight(x0_predecessor, x0) 
    + g.get_edge_weight(x0, x0_successor) + g.get_edge_weight(y1, y2);
    auto new_length = g.get_edge_weight(x0_predecessor, x0_successor)
    + g.get_edge_weight(y1, x0) + g.get_edge_weight(x0, y2);
    return prev_length - new_length;
}

/*
Shortens tour by repeating 2.5-opt moves until no improvement
can by done: in every iteration immediatelly makes permanent
the first move found that gives any length gain.
 */

void TwoHalfOpt::solve() {
    tour_cost -= g.get_edge_weight(tour[g.get_number_of_vertices() - 1], tour[g.get_number_of_vertices()]);
    tour.pop_back();
    auto start = chrono::high_resolution_clock::now();
    auto locally_optimal = false;
    int i, j, x1, x2, v0, y1, y2;
    long double best_improvement;
    int best_i, best_j;
    bool is_two_opt;
    while (!locally_optimal) {
        locally_optimal = true;
        best_improvement = 0;
        is_two_opt = true;
        for (int counter_1 = 0; counter_1 < g.get_number_of_vertices() - 2; counter_1++) {
            i = counter_1;
            x1 = tour[i];
            x2 = tour[(i + 1) % g.get_number_of_vertices()];

            for (int counter_2 = counter_1 + 2; counter_2 < g.get_number_of_vertices(); counter_2++) {
                j = counter_2;
                y1 = tour[j];
                y2 = tour[(j + 1) % g.get_number_of_vertices()];

                auto two_opt_improvement = calculate_improvement(x1, x2, y1, y2);
                if (two_opt_improvement - best_improvement > THRESHOLD) {
                    best_improvement = two_opt_improvement;
                    best_i = i;
                    best_j = j;
                    is_two_opt = true;
                    locally_optimal = false;
                } else {
                    v0 = tour[(i + 2) % g.get_number_of_vertices()];
                    if (v0 != y1) {
                        auto node_shift_improvement = calculate_node_shift_improvement(x1, x2, v0, y1, y2);
                        if (node_shift_improvement - best_improvement > THRESHOLD) {
                            best_improvement = node_shift_improvement;
                            best_i = (i + 1) % g.get_number_of_vertices();
                            best_j = j;
                            is_two_opt = false;
                            locally_optimal = false;
                        }
                    } else {
                        v0 = tour[(g.get_number_of_vertices() + j - 1) % g.get_number_of_vertices()];
                        if (v0 != x2) {
                            auto node_shift_improvement = calculate_node_shift_improvement(v0, y1, y2, x1, x2);
                            if (node_shift_improvement - best_improvement > THRESHOLD) {
                                best_improvement = node_shift_improvement;
                                best_i = j;
                                best_j = i;
                                is_two_opt = false;
                                locally_optimal = false;
                            }
                        }
                    }
                }
            }
        }
        if (!locally_optimal) {
            if (is_two_opt) {
                apply_change(best_i, best_j); // Apply 2-opt move
            } else {
                node_shift(best_i, best_j);  // Apply node-shift move
            }
        }
    }
    tour.push_back(tour[0]);
    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();
    compute_tour_cost();
}
