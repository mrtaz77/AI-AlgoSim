#pragma once

#include <bits/stdc++.h>
#include "Constructive.hpp"

using namespace std;

class FarthestInsertion : public Constructive {
    vector<long double> minimum_distances_to_tour;

    pair<int, int> find_nodes_farthest_apart();
    void compute_tour_cost();
public:
    FarthestInsertion(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
    void initialize_distances_to_tour(int, int);
    bool is_start_variable() override;
};