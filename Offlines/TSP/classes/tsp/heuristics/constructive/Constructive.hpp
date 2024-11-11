#pragma once

#include "Versions.hpp"
#include "../Heuristic.hpp"

class Constructive : public Heuristic {
    Versions version;
protected:
    int starting_node;
public:
    Constructive(Graph&);
    void set_version(Versions version);
    Versions get_version() const;
    int select_from_candidates(const vector<pair<int, long double>>&);
    void set_starting_node(int);
};