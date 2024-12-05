#pragma once

#include "AttributeSelector.hpp"

class RandomTopAttribute : public AttributeSelector
{
  int max_top_attributes;
public:
  RandomTopAttribute(int);
  int select(const vector<pair<int, double>>& attribute_scores) const override;
};