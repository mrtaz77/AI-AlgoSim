
#pragma once

#include "Validator.hpp"

using namespace std;

class ColumnValidator : public Validator 
{
  public:
    bool validate(const string&) override;
};
