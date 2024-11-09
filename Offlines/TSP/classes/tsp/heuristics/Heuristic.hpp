#pragma once

#include <bits/stdc++.h>
#include "../../graph/Graph.hpp"

using namespace std;

class Heuristic {
protected:
    Graph& g;
    vector<int> tour;
    long double tour_cost;
    long double time_taken;

public:
    Heuristic(Graph& graph);

    virtual ~Heuristic() = default;

    virtual void solve() = 0;

    vector<int>& get_tour();
    long double get_time_taken() const;
    long double get_tour_cost() const;
};
