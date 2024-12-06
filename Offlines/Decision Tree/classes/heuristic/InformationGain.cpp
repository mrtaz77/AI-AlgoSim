#include "InformationGain.hpp"

double
InformationGain::current_entropy(const vector<vector<string>>& dataset)
{
  map<string, int> class_count;
  for (const auto& data : dataset)
  {
    class_count[data.back()]++;
  }

  double entropy = 0.0;
  size_t total_rows = dataset.size();
  for (const auto& [_, count] : class_count)
  {
    double probability = static_cast<double>(count) / total_rows;
    entropy -= probability * log2(probability);
  }
  return entropy;
}

double
InformationGain::calculate(const vector<vector<string>>& dataset, int attribute_index)
{
  double entropy_before_split = current_entropy(dataset);

  map<string, vector<vector<string>>> partitions;

  for (const auto& data : dataset)
  {
    partitions[data[attribute_index]].push_back(data);
  }

  double weighted_entropy = 0.0;
  size_t total_rows = dataset.size();

  for (const auto& [_, subset] : partitions)
  {
    double subset_size = subset.size();
    double subset_entropy = current_entropy(subset);
    double probability = static_cast<double>(subset_size) / total_rows;
    weighted_entropy += (probability * subset_entropy);
  }

  return entropy_before_split - weighted_entropy;
}