#include "RandomTopAttribute.hpp"

RandomTopAttribute::RandomTopAttribute(int max_top_attributes) : max_top_attributes(max_top_attributes) {}

int
RandomTopAttribute::select(const vector<pair<int, double>>& attribute_scores) const {
  vector<pair<int, double>> top(attribute_scores);
  sort(top.begin(), top.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
  top.resize(min(max_top_attributes, static_cast<int>(top.size())));

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, top.size() - 1);
  return top[dist(gen)].first;
}