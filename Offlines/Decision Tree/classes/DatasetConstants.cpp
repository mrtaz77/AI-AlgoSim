#include "DatasetConstants.hpp"

string 
attribute_name(int attribute_index)
{
  switch(attribute_index)
  {
    case 0: return "buying";
    case 1: return "maint";
    case 2: return "doors";
    case 3: return "persons";
    case 4: return "lug_boot";
    case 5: return "safety";
    case 6: return "class";
  }
  return "unknown";
}