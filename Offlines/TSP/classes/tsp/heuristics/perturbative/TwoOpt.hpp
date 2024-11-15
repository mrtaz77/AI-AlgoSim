#pragma once

#include <bits/stdc++.h>
#include "Perturbative.hpp"

using namespace std;

class TwoOpt : public Perturbative {
public:
    TwoOpt(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
    void apply_change(int, int) override;
    long double calculate_improvement(int, int, int, int);
};