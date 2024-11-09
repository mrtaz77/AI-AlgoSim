#pragma once

#include "Versions.hpp"
#include "../Heuristic.hpp"

class Constructive : public Heuristic {
    Versions version = Versions::GREEDY;
public:
    Constructive(Graph& graph) : Heuristic(graph) {}
    virtual void solve() override = 0;
    void set_version(Versions version);
    Versions get_version() const;

    int select_from_candidates(const vector<pair<int, long double>>&);
};