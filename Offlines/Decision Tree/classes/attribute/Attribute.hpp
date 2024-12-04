#pragma once

#include <bits/stdc++.h>

using namespace std;

class Attribute
{
public:
  virtual int select(const vector<pair<int, double>>& attribute_scores) const = 0;
  virtual ~Attribute() = default;
};