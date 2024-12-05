#pragma once

#include "attribute/AttributeSelector.hpp"
#include "heuristic/Heuristic.hpp"
#include "heuristic/InformationGain.hpp"
#include "tree/DecisionTree.hpp"
#include "tree/InternalNode.hpp"
#include "tree/TerminalNode.hpp"
#include "DatasetConstants.hpp"

class TreeBuilder
{
  shared_ptr<Heuristic> heuristic;
  shared_ptr<AttributeSelector> attribute_selector;
  shared_ptr<DecisionTree> root;

  shared_ptr<DecisionTree> build_tree_recursively(const vector<vector<string>>&, const vector<int>&, const vector<string>&);
  bool all_labels_are_same(const vector<vector<string>>&);
  int select_best_attribute(const vector<vector<string>>&, const vector<int>&);
  unordered_map<string, vector<vector<string>>> partition_data(const vector<vector<string>>&, int);
  string find_plurality_label(const vector<string>&);
  vector<string> get_labels(const vector<vector<string>>&);
public:
  TreeBuilder(shared_ptr<Heuristic>, shared_ptr<AttributeSelector>);
  shared_ptr<DecisionTree> build_tree(const vector<vector<string>>&);
  void set_heuristic(shared_ptr<Heuristic>);
  void set_attribute(shared_ptr<AttributeSelector>);
  double calculate_accuracy(const vector<vector<string>>&);
};