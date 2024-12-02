#include <iostream>
#include "classes/validator/ColumnValidator.hpp"
#include "classes/validator/FileExists.hpp"
#include "classes/validator/RowValidator.hpp"
#include "classes/validator/Validator.hpp"

using namespace std;

int 
main(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  string file_path = argv[1];
  shared_ptr<Validator> file_check = make_shared<FileExists>();
  shared_ptr<Validator> column_check = make_shared<ColumnValidator>();
  shared_ptr<Validator> row_check = make_shared<RowValidator>();

  file_check->set_next(column_check);
  column_check->set_next(row_check);

  if (file_check->validate(file_path))
  {
    cout << "Validation successful." << endl;
    return 0;
  }
  return 1;
}