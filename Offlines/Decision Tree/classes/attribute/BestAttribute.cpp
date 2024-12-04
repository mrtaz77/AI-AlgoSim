#include "BestAttribute.hpp"

int
BestAttribute::select(const vector<pair<int, double>>& attribute_scores) const
{
  return max_element(attribute_scores.begin(), attribute_scores.end(), 
    [](const pair<int, double>& a, const pair<int, double>& b) 
    {
      return a.second < b.second;
    })->first;
}