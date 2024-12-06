#include "GiniImpurity.hpp"

double
GiniImpurity::current_gini_impurity(const vector<vector<string>>& dataset)
{
  map<string, int> class_count;
  for (const auto& data : dataset)
  {
    class_count[data.back()]++;
  }

  double gini_impurity = 1.0;
  size_t total_rows = dataset.size();
  for (const auto& [_, count] : class_count)
  {
    double probability = static_cast<double>(count) / total_rows;
    gini_impurity -= (probability * probability);
  }

  return gini_impurity;
}

double
GiniImpurity::calculate(const vector<vector<string>>& dataset, int attribute_index)
{
  map<string, vector<vector<string>>> partitions;
  for (const auto& row : dataset)
    partitions[row[attribute_index]].push_back(row);

  double weighted_gini_impurity = 0.0;
  size_t total_rows = dataset.size();

  for (const auto& [_, subset] : partitions)
  {
    double subset_size = subset.size();
    double subset_gini_impurity = current_gini_impurity(subset);
    weighted_gini_impurity += (static_cast<double>(subset_size) / total_rows) * subset_gini_impurity;
  }

  return -weighted_gini_impurity;
}