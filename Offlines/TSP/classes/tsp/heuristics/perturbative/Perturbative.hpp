#pragma once

#include "../Heuristic.hpp"

class Perturbative : public Heuristic {
protected:
    virtual long double calculate_improvement(int, int) = 0;
    virtual void apply_change(int, int) = 0;

public:
    Perturbative(Graph&);
    void set_tour(vector<int>&);
    void set_cost(long double);
};