#pragma once

#include <bits/stdc++.h>

using namespace std;

class Validator
{
protected:
    shared_ptr<Validator> next_validator;

public:
    Validator() : next_validator(nullptr) {}
    void set_next(shared_ptr<Validator>);
    virtual bool validate(const string&) = 0;
    virtual ~Validator() {}
};