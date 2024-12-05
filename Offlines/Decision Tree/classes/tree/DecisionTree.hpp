#pragma once

#include <bits/stdc++.h>

using namespace std;

class DecisionTree
{
public:
  virtual string classify(const vector<string>& instance) const = 0;
  virtual ~DecisionTree() = default;
};