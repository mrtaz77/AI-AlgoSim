#include "FileExists.hpp"

bool 
FileExists::validate(const string& file_path)
{
  ifstream file(file_path);
  if (!file.is_open()) {
      cout << "Error: File does not exist or cannot be opened." << endl;
      return false;
  }
  file.close();
  return next_validator ? next_validator->validate(file_path) : true;
}