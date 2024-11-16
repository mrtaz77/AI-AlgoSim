#pragma once

#include <bits/stdc++.h>
#include "Perturbative.hpp"

using namespace std;

class TwoHalfOpt : public Perturbative {
public:
    TwoHalfOpt(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
    void apply_change(int, int) override;
    long double calculate_improvement(int, int, int, int);
    long double calculate_node_shift_improvement(int, int, int, int, int);
    void node_shift(int, int);
};