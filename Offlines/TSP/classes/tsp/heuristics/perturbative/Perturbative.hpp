#pragma once

#include "../Heuristic.hpp"

class Perturbative : public Heuristic {
protected:
    virtual long double calculate_improvement(int, int) = 0;
    virtual void apply_change(int, int) = 0;

public:
    Perturbative(Graph&);
    virtual void solve() override = 0;
    virtual const string& get_heuristic_name() const override = 0;
    void set_tour(vector<int>&);
    void set_cost(long double);
};