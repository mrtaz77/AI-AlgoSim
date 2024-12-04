#pragma once

#include "Attribute.hpp"

class RandomAttributeTop3 : public Attribute
{
public:
  int select(const vector<pair<int, double>>& attribute_scores) const override;
};