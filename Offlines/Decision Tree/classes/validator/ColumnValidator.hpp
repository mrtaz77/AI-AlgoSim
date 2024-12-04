
#pragma once

#include "../DatasetConstants.hpp"
#include "Validator.hpp"

using namespace std;

class ColumnValidator : public Validator 
{
  public:
    bool validate(const string&) override;
};
