#pragma once

#include <bits/stdc++.h>
#include "Constructive.hpp"

using namespace std;

class NearestNeighbour : public Constructive {
public:
    NearestNeighbour(Graph& graph) : Constructive(graph) {}
    void solve() override;
}; 