#include "classes/util/util.hpp"

int 
main(int argc, char* argv[])
{
  try 
  {
    string file_path;
    int runs;

    validate_args(argc, argv, file_path, runs);
    validate_file(file_path);

    Dataset dataset = load_dataset(file_path);
    train_and_test(dataset, runs);

    return 0;
  } 
  catch (const exception& ex) 
  {
    cout << ex.what() << endl;
    return 1;
  }
}