#pragma once

#include "Heuristic.hpp"
#include "H1.hpp"
#include "H2.hpp"
#include "H3.hpp"
#include "H4.hpp"
using namespace std;

class HeuristicFactory {
public:
    static Heuristic* create_heuristic(Heuristics);
};