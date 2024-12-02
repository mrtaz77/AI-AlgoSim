#pragma once

#include "Validator.hpp"

using namespace std;

class RowValidator : public Validator
{
  set<string> valid_buying{"vhigh", "high", "med", "low"};
  set<string> valid_maint{"vhigh", "high", "med", "low"};
  set<string> valid_doors{"2", "3", "4", "5more"};
  set<string> valid_persons{"2", "4", "more"};
  set<string> valid_lug_boot{"small", "med", "big"};
  set<string> valid_safety{"low", "med", "high"};
  set<string> valid_class{"unacc", "acc", "good", "vgood"};
  
  bool is_valid_row(const vector<string>&);

  public:
    bool validate(const string&) override;
};