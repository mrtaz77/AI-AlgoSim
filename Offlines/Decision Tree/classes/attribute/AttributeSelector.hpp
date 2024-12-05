#pragma once

#include <bits/stdc++.h>

using namespace std;

class AttributeSelector
{
public:
  virtual int select(const vector<pair<int, double>>& attribute_scores) const = 0;
  virtual ~AttributeSelector() = default;
};