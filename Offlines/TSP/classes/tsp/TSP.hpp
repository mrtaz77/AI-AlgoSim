#pragma once

#include <bits/stdc++.h>
#include "../graph/Graph.hpp"
#include "heuristics/Heuristic.hpp"
#include "heuristics/Heuristics.hpp"
#include "heuristics/Constructive/NearestNeighbour.hpp"

using namespace std;

class TSP {
    Graph& g;
    unique_ptr<Heuristic> heuristic;
public:
    TSP(Graph&);
    void run();
    void set_heuristic(Heuristics);
    void set_graph(Graph&);
    string get_heuristic_name() const;
    vector<int>& get_tour();
    long double get_cost() const;
    long double get_time() const;
};