#pragma once

#include <bits/stdc++.h>

#include "Heuristic.hpp"

using namespace std;

class InformationGain : public Heuristic
{
public:
  double calculate(const vector<vector<string>>& dataset, int attribute_index) const override;
};