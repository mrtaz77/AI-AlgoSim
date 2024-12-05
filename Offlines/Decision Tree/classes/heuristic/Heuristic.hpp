#pragma once

#include <bits/stdc++.h>

using namespace std;

class Heuristic
{
public:
  virtual double calculate(const vector<vector<string>>& dataset, int attribute_index) = 0;
  virtual ~Heuristic() = default;
};