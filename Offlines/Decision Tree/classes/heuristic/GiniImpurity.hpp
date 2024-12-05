#include "Heuristic.hpp"

class GiniImpurity : public Heuristic
{
public:
  double current_gini_impurity(const vector<vector<string>>& dataset);
  double calculate(const vector<vector<string>>& dataset, int attribute_index) override;
};