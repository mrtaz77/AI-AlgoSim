#pragma once

#include <bits/stdc++.h>
#include "../graph/Graph.hpp"
#include "heuristics/Heuristic.hpp"
#include "heuristics/Heuristics.hpp"
#include "heuristics/constructive/NearestNeighbour.hpp"
#include "heuristics/constructive/FarthestInsertion.hpp"
#include "heuristics/constructive/MST.hpp"
#include "heuristics/constructive/Constructive.hpp"
#include "heuristics/constructive/Versions.hpp"
#include "heuristics/perturbative/Perturbative.hpp"
#include "heuristics/perturbative/TwoOpt.hpp"

using namespace std;

class TSP {
    Graph& graph;
    unique_ptr<Constructive> constructive_heuristic;
    unique_ptr<Perturbative> perturbative_heuristic;
    pair<long double, long double> tour_avg_costs, tour_min_costs, tour_max_costs;
    pair<long double, long double> tour_avg_times, tour_min_times, tour_max_times;
public:
    TSP(Graph&);
    void run();
    void set_heuristics(Heuristics, Heuristics);
    void set_version(Versions);
    void set_graph(Graph&);
    const string get_heuristic_name(Heuristics) const;
    long double get_avg_cost(Heuristics) const;
    long double get_best_cost(Heuristics) const;
    long double get_worst_cost(Heuristics) const;
    const Graph& get_graph() const;
    Versions get_version() const;
    long double get_avg_time(Heuristics) const;
    long double get_best_time(Heuristics) const;
    long double get_worst_time(Heuristics) const;
};