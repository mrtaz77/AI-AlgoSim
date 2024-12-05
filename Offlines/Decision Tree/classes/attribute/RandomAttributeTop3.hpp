#pragma once

#include "AttributeSelector.hpp"

class RandomAttributeTop3 : public AttributeSelector
{
public:
  int select(const vector<pair<int, double>>& attribute_scores) const override;
};