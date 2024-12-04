#include <iostream>
#include "classes/validator/ColumnValidator.hpp"
#include "classes/validator/FileExists.hpp"
#include "classes/validator/RowValidator.hpp"
#include "classes/validator/Validator.hpp"
#include "classes/Dataset.hpp"
#include "classes/DatasetConstants.hpp"

using namespace std;

int 
main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: " << argv[0] << " <input file> <number of runs>" << endl;
    return 1;
  }

  string file_path = argv[1];
  shared_ptr<Validator> file_check = make_shared<FileExists>();
  shared_ptr<Validator> column_check = make_shared<ColumnValidator>();
  shared_ptr<Validator> row_check = make_shared<RowValidator>();

  file_check->set_next(column_check);
  column_check->set_next(row_check);

  if (!file_check->validate(file_path))
  {
    cout << "Invalid file." << endl;
    return 1;
  }

  Dataset dataset;
  ifstream file(file_path);

  file >> dataset;

  int runs = stoi(argv[2]);

  if(runs < 1)
  {
    cout << "Number of runs must be greater than 0." << endl;
    return 1;
  }

  for(int i = 0; i < runs; i++)
  {
    auto [train, test] = dataset.split(TRAINING_SPLIT_RATIO);
  }

  return 0;
}