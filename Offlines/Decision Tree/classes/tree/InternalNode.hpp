#pragma once

#include "DecisionTree.hpp"
#include "../DatasetConstants.hpp"

class InternalNode : public DecisionTree
{
  int attribute_index;
  map<string, shared_ptr<DecisionTree>> children;
public:
  InternalNode(int);
  void add_child(const string&, shared_ptr<DecisionTree>);
  string classify(const vector<string>&) const override;
  void print(ostream&, int) const override;
};
