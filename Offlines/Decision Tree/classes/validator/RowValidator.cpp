#include "RowValidator.hpp"

bool 
RowValidator::is_valid_row(const vector<string>& row)
{
  return valid_buying.count(row[0])   &&
         valid_maint.count(row[1])    &&
         valid_doors.count(row[2])    &&
         valid_persons.count(row[3])  &&
         valid_lug_boot.count(row[4]) &&
         valid_safety.count(row[5])   &&
         valid_class.count(row[6]);
}

bool 
RowValidator::validate(const string& file_path)
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
    if (!is_valid_row(columns)) {
        cout << "Error: Invalid row data." << endl;
        return false;
    }
  }
  file.close();
  return next_validator ? next_validator->validate(file_path) : true;
}