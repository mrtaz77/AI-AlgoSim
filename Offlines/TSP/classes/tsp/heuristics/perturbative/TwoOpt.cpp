#include "TwoOpt.hpp"

TwoOpt::TwoOpt(Graph& graph) : Perturbative(graph) {}

long double TwoOpt::calculate_improvement(int x1, int x2, int y1, int y2) {
    auto prev_length = g.get_edge_weight(x1, x2) + g.get_edge_weight(y1, y2);
    auto new_length = g.get_edge_weight(x1, y1) + g.get_edge_weight(x2, y2);
    return prev_length - new_length;
}

void TwoOpt::apply_change(int i, int j) {
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

// Shortens the tour by repeating 2-opt moves until no improvement
// can by done; in every iteration looks for and applies the move
// that gives maximal length gain.
void TwoOpt::solve() {
    tour_cost -= g.get_edge_weight(tour[g.get_number_of_vertices() - 1], tour[g.get_number_of_vertices()]);
    tour.pop_back();
    auto start = chrono::high_resolution_clock::now();
    int best_move_i, best_move_j;
    long double best_move_improvement;
    bool locally_optimal = false;
    int i, j, x1, y1, x2, y2, counter_2_limit;
    long double expected_improvement;
    while(!locally_optimal) {
        locally_optimal = true;
        best_move_improvement = 0;
        for(int counter_1 = 0; counter_1 < g.get_number_of_vertices() - 2; counter_1++) {
            i = counter_1;
            x1 = tour[i];
            x2 = tour[(i + 1) % g.get_number_of_vertices()];
            counter_2_limit = (i == 0) ? g.get_number_of_vertices() - 2 : g.get_number_of_vertices() - 1;
            for(int counter_2 = i + 2; counter_2 <= counter_2_limit; counter_2++) {
                j = counter_2;
                y1 = tour[j];
                y2 = tour[(j + 1) % g.get_number_of_vertices()];
                expected_improvement = calculate_improvement(x1, x2, y1, y2);
                if(expected_improvement - best_move_improvement > THRESHOLD) {
                    best_move_improvement = expected_improvement;
                    best_move_i = i;
                    best_move_j = j;
                    locally_optimal = false;
                }
            }
        }
        if(!locally_optimal) {
            apply_change(best_move_i, best_move_j);
        }
    }
    tour.push_back(tour[0]);
    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();
    compute_tour_cost();

}

const string TwoOpt::get_heuristic_name() const { return "2opt"; }