#pragma once

#include <bits/stdc++.h>
#include "Constructive.hpp"

using namespace std;

class MST : public Constructive {
    void dfs(int, vector<bool>&, vector<vector<int>>&);
    vector<vector<int>> build_mst(const vector<int>&);
public:
    MST(Graph&);
    void solve() override;
    const string get_heuristic_name() const override;
    bool is_start_variable() override;
};