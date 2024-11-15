#pragma once

#include "Perturbative.hpp"

using namespace std;

class NodeShift : public Perturbative {
public:
    NodeShift(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
    void apply_change(int, int) override;
    long double calculate_improvement(int, int, int, int, int);
};