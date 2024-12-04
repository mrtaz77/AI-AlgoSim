#include "RandomAttributeTop3.hpp"

int
RandomAttributeTop3::select(const vector<pair<int, double>>& attribute_scores) const {
  vector<pair<int, double>> top_3(attribute_scores);
  sort(top_3.begin(), top_3.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
  top_3.resize(min(3, static_cast<int>(top_3.size())));

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, top_3.size() - 1);
  return top_3[dist(gen)].first;
}