#include "Heuristic.hpp"

class GiniImpurity : public Heuristic
{
public:
  double calculate(const vector<vector<string>>& dataset, int attribute_index) const override;
};