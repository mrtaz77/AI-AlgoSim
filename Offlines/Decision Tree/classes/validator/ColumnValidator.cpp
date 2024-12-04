#include "ColumnValidator.hpp"

bool ColumnValidator::validate(const string& file_path)
{
  ifstream file(file_path);
  string line;
  while (getline(file, line)) {
    istringstream stream(line);
    vector<string> columns;
    string value;
    while (getline(stream, value, ',')) {
        columns.push_back(value);
    }
    if (columns.size() != N_COLS) {
        cout << "Error: Each row must have exactly " << N_COLS << " columns." << endl;
        return false;
    }
  }
  file.close();
  return next_validator ? next_validator->validate(file_path) : true;
}