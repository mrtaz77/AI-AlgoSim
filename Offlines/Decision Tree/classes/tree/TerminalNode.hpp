#pragma once

#include "DecisionTree.hpp"

class TerminalNode : public DecisionTree
{
  string result;
public:
  TerminalNode(const string&);
  string classify(const vector<string>&) const override;
};