#pragma once

#include <bits/stdc++.h>

using namespace std;

class Heuristic
{
public:
  virtual double calculate(const vector<vector<string>>& dataset, int attribute_index) const = 0;
  virtual ~Heuristic() = default;
};