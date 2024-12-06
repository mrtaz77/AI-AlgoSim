#include "classes/util/util.hpp"

int 
main(int argc, char* argv[])
{
  try 
  {
    string file_path;
    int runs;
    double train_split_ratio;

    validate_args(argc, argv, file_path, runs, train_split_ratio);
    validate_file(file_path);

    Dataset dataset = load_dataset(file_path);
    train_and_test(dataset, runs, train_split_ratio);

    return 0;
  } 
  catch (const exception& ex) 
  {
    cout << ex.what() << endl;
    return 1;
  }
}