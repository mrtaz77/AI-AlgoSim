#pragma once

#include "Attribute.hpp"

class BestAttribute : public Attribute
{
public:
  int select(const vector<pair<int, double>>& attribute_scores) const override;
};