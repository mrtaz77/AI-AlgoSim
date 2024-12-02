#pragma once

#include "Validator.hpp"

using namespace std;

class FileExists : public Validator
{
  public:
    bool validate(const string&) override;
};
