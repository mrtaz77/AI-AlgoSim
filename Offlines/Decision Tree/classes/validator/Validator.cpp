#include "Validator.hpp"

void Validator::set_next(shared_ptr<Validator> next)
{
  next_validator = next;
}