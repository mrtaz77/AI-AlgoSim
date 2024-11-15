#pragma once

#include "../Heuristic.hpp"

#define THRESHOLD 0.001

class Perturbative : public Heuristic {
protected:
    virtual void apply_change(int, int) = 0;

public:
    Perturbative(Graph&);
    void set_tour(vector<int>&);
    void set_cost(long double);
};