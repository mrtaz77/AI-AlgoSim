#include "TreeBuilder.hpp"

TreeBuilder::TreeBuilder(shared_ptr<Heuristic> heuristic, shared_ptr<AttributeSelector> attribute_selector)
: heuristic(heuristic), attribute_selector(attribute_selector) {}

void
TreeBuilder::set_heuristic(shared_ptr<Heuristic> heuristic)
{
  this->heuristic = heuristic;
}

void
TreeBuilder::set_attribute(shared_ptr<AttributeSelector> attribute_selector)
{
  this->attribute_selector = attribute_selector;
}

shared_ptr<DecisionTree>
TreeBuilder::build_tree(const vector<vector<string>>& dataset)
{
  vector<int> attributes;
  for(int i = 0; i < ATTRIBUTES; i++)
    attributes.push_back(i);
  root = build_tree_recursively(dataset, attributes, dataset);
  return root;
}

shared_ptr<DecisionTree>
TreeBuilder::build_tree_recursively(const vector<vector<string>>& examples, const vector<int>& attributes, const vector<vector<string>>& parent_examples)
{
  /**
   * No example has been observed for
   * this combination of attributes
   * return default value
   * aka plurality of parent_labels
  */
  if(examples.empty()) {
    auto plurality_label = find_plurality_label(parent_examples);
    return make_shared<TerminalNode>(plurality_label);
  }

  /**
   * All examples have the same label
   * return a leaf node with that label
  */
  if(all_labels_are_same(examples)) {
    return make_shared<TerminalNode>(examples[0].back());
  }

  /**
   * No attributes left to split on
   * all examples have the same description but different classifications
   * Possible error or noise in data
   * return plurality of examples
  */
  if(attributes.size() == 0) {
    auto plurality_label = find_plurality_label(examples);
    return make_shared<TerminalNode>(plurality_label);
  }

  int best_attribute = select_best_attribute(examples, attributes);
  auto node = make_shared<InternalNode>(best_attribute);  
  auto partitions = partition_data(examples, best_attribute);

  vector<int> remaining_attributes = attributes;
  remaining_attributes.erase(find(remaining_attributes.begin(), remaining_attributes.end(), best_attribute));  
  
  for(const auto& [attribute_value, partition] : partitions) 
  {
    node->add_child(attribute_value, build_tree_recursively(partition, remaining_attributes, examples));
  }
  return node;
}

string
TreeBuilder::find_plurality_label(const vector<vector<string>>& examples)
{

  map<string, int> label_counts;
  for(const auto& example : examples)
  {
    label_counts[example.back()]++;
  }
  
  int max_count = 0;
  string max_label = "";
  for (const auto& [label, count] : label_counts)
  {
    if(count > max_count)
    {
      max_count = count;
      max_label = label;
    }
  }
  return max_label;
}

bool
TreeBuilder::all_labels_are_same(const vector<vector<string>>& examples)
{
  string first_label = examples[0].back();
  for(const auto& example : examples)
  {
    if(example.back() != first_label)
      return false;
  }
  return true;
}

map<string, vector<vector<string>>>
TreeBuilder::partition_data(const vector<vector<string>>& examples, int attribute_index)
{
  map<string, vector<vector<string>>> partitions;
  for(const auto& example : examples)
    partitions[example[attribute_index]].push_back(example);

  for (const auto& attribute_value : attribute_values[attribute_index])
  {
    if (partitions.find(attribute_value) == partitions.end())
    {
      partitions[attribute_value] = {};
    }
  }
  
  return partitions;
}

int
TreeBuilder::select_best_attribute(const vector<vector<string>>& examples, const vector<int>& attributes)
{
  vector<pair<int, double>> attribute_scores;
  for(int attribute : attributes)
  {
    double score = heuristic->calculate(examples, attribute);
    attribute_scores.push_back({attribute, score});
  }
  return attribute_selector->select(attribute_scores);
}

double
TreeBuilder::calculate_accuracy(const vector<vector<string>>& test)
{
  int correct_predictions = 0;
  int total_predictions = test.size();

  for(const auto& row : test)
  {
    string actual_label = row.back();
    string predicted_label = root->classify(row);
    if(actual_label == predicted_label)
      correct_predictions++;
  }
  return static_cast<double>(correct_predictions * 100.0) / total_predictions;
}

ostream& operator<<(ostream& os, const TreeBuilder& tree_builder)
{
  tree_builder.root->print(os, 0);
  return os;
}