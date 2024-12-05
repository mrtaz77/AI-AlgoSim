#pragma once

#include "AttributeSelector.hpp"

class BestAttribute : public AttributeSelector
{
public:
  int select(const vector<pair<int, double>>& attribute_scores) const override;
};