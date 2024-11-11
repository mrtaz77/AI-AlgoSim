#pragma once

#include <bits/stdc++.h>
#include "Constructive.hpp"

using namespace std;

class NearestNeighbour : public Constructive {
public:
    NearestNeighbour(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
}; 