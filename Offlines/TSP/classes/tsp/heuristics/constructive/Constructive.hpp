#pragma once

#include "../Heuristic.hpp"

class Constructive : public Heuristic {
public:
    Constructive(Graph& graph) : Heuristic(graph) {}
    virtual void solve() override = 0;
};