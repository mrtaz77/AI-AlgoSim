#include "util.hpp"

void
validate_args(int argc, char *argv[], string& file_path, int& runs)
{
  if (argc != 3)
  {
    throw invalid_argument("Usage: " + string(argv[0]) + " <input file> <number of runs>");
  }

  file_path = argv[1];

  try {
    runs = stoi(argv[2]);
    if(runs < 1)
    {
      throw invalid_argument("Number of runs must be greater than 0.");
    }
  } 
  catch (const invalid_argument& e) 
  {
    throw invalid_argument("Number of runs must be an integer.");
  }
}

void
validate_file(const string& file_path) 
{
  shared_ptr<Validator> file_check = make_shared<FileExists>();
  shared_ptr<Validator> column_check = make_shared<ColumnValidator>();
  shared_ptr<Validator> row_check = make_shared<RowValidator>();

  file_check->set_next(column_check);
  column_check->set_next(row_check);

  if (!file_check->validate(file_path)) 
  {
    throw runtime_error("Invalid file: failed validation checks.");
  }
}

Dataset
load_dataset(const string& file_path)
{
  Dataset dataset;
  ifstream file(file_path);

  file >> dataset;

  return dataset;
}

void
train_and_test(Dataset& dataset, int runs)
{
  vector<double> accuracies_best_ig, accuracies_top3_ig, accuracies_best_gini, accuracies_top3_gini;
  vector<double> training_times_best_ig, training_times_top3_ig, training_times_best_gini, training_times_top3_gini;

  auto ig = make_shared<InformationGain>();
  auto gini = make_shared<GiniImpurity>();
  auto best = make_shared<BestAttribute>();
  auto random_top = make_shared<RandomTopAttribute>(MAX_TOP_ATTRIBUTES);

  if (fs::exists(TREES_FOLDER))
    fs::remove_all(TREES_FOLDER);
  fs::create_directory(TREES_FOLDER);

  for(int i = 0; i < runs; i++)
  {
    auto [train, test] = dataset.split(TRAINING_SPLIT_RATIO);

    auto train_set = train.get_dataset();
    auto test_set = test.get_dataset();

    string run_folder = string(TREES_FOLDER) + "/run_" + to_string(i + 1);
    fs::create_directory(run_folder);

    auto start = chrono::high_resolution_clock::now();
    auto tree_builder = make_shared<TreeBuilder>(ig, best);
    tree_builder->build_tree(train_set);
    auto end = chrono::high_resolution_clock::now();
    training_times_best_ig.push_back(chrono::duration_cast<chrono::microseconds>(end - start).count());
    accuracies_best_ig.push_back(tree_builder->calculate_accuracy(test_set));
    print_tree(tree_builder, run_folder + "/best_ig.txt");

    start = chrono::high_resolution_clock::now();
    tree_builder = make_shared<TreeBuilder>(ig, random_top);
    tree_builder->build_tree(train_set);
    end = chrono::high_resolution_clock::now();
    training_times_top3_ig.push_back(chrono::duration_cast<chrono::microseconds>(end - start).count());
    accuracies_top3_ig.push_back(tree_builder->calculate_accuracy(test_set));
    print_tree(tree_builder, run_folder + "/top" + to_string(MAX_TOP_ATTRIBUTES) + "_ig.txt");

    start = chrono::high_resolution_clock::now();
    tree_builder = make_shared<TreeBuilder>(gini, random_top);
    tree_builder->build_tree(train_set);
    end = chrono::high_resolution_clock::now();
    training_times_top3_gini.push_back(chrono::duration_cast<chrono::microseconds>(end - start).count());
    accuracies_top3_gini.push_back(tree_builder->calculate_accuracy(test_set));
    print_tree(tree_builder, run_folder + "/top" + to_string(MAX_TOP_ATTRIBUTES) + "_gini.txt");

    start = chrono::high_resolution_clock::now();
    tree_builder = make_shared<TreeBuilder>(gini, best);
    tree_builder->build_tree(train_set);
    end = chrono::high_resolution_clock::now();
    training_times_best_gini.push_back(chrono::duration_cast<chrono::microseconds>(end - start).count());
    accuracies_best_gini.push_back(tree_builder->calculate_accuracy(test_set));
    print_tree(tree_builder, run_folder + "/best_gini.txt");
  }

  statistics(accuracies_best_ig, accuracies_top3_ig, accuracies_best_gini, accuracies_top3_gini);
  write_accuracies_and_times_to_csv(accuracies_best_ig, 
                                    accuracies_top3_ig, 
                                    accuracies_best_gini, 
                                    accuracies_top3_gini, 
                                    training_times_best_ig, 
                                    training_times_top3_ig, 
                                    training_times_best_gini, 
                                    training_times_top3_gini);
}

double
calculate_average(vector<double>& accuracies)
{
  double sum = accumulate(accuracies.begin(), accuracies.end(), 0.0);
  return sum / accuracies.size();
}

void
statistics(
  vector<double>& accuracies_best_ig,
  vector<double>& accuracies_top3_ig,
  vector<double>& accuracies_best_gini,
  vector<double>& accuracies_top3_gini
)
{
  auto avg_accuracy_best_ig = calculate_average(accuracies_best_ig);
  auto avg_accuracy_top3_ig = calculate_average(accuracies_top3_ig);
  auto avg_accuracy_best_gini = calculate_average(accuracies_best_gini);
  auto avg_accuracy_top3_gini = calculate_average(accuracies_top3_gini);

  auto std_dev_best_ig = calculate_standard_deviation(accuracies_best_ig);
  auto std_dev_top3_ig = calculate_standard_deviation(accuracies_top3_ig);
  auto std_dev_best_gini = calculate_standard_deviation(accuracies_best_gini);
  auto std_dev_top3_gini = calculate_standard_deviation(accuracies_top3_gini);

  auto cv_best_ig = calculate_coefficient_of_variation(accuracies_best_ig);
  auto cv_top3_ig = calculate_coefficient_of_variation(accuracies_top3_ig);
  auto cv_best_gini = calculate_coefficient_of_variation(accuracies_best_gini);
  auto cv_top3_gini = calculate_coefficient_of_variation(accuracies_top3_gini);

  size_t runs = accuracies_best_ig.size();

  cout << "+-------------------------------------------+----------------------------------+----------------------------------+----------------------------------+" << endl;
  cout << "|              # of Runs = " << setw(2) << runs << "               |         Average accuracy         |        Standard Deviation        |     Co-efficient of Variation    |" << endl;
  cout << "+-------------------------------------------+------------------+---------------+----------------------------------+----------------------------------+" << endl;
  cout << "|       Attribute Selection Strategy        | Information gain | Gini Impurity | Information gain | Gini Impurity | Information gain | Gini Impurity |" << endl;
  cout << "+-------------------------------------------+------------------+---------------+------------------+---------------+------------------+---------------+" << endl;
  cout << "|          Always select the best           | "
       << setw(10) << fixed << setprecision(2) << avg_accuracy_best_ig << " %     | "
       << setw(8) << fixed << setprecision(2) << avg_accuracy_best_gini << " %    | "
       << setw(10) << fixed << setprecision(2) << std_dev_best_ig << "       | "
       << setw(8) << fixed << setprecision(2) << std_dev_best_gini << "      | "
       << setw(10) << fixed << setprecision(2) << cv_best_ig << "       | "
       << setw(9) << fixed << setprecision(2) << cv_best_gini << "     |" << endl;
  cout << "+-------------------------------------------+------------------+---------------+------------------+---------------+------------------+---------------+" << endl;
  cout << "| Select one randomly from top " << MAX_TOP_ATTRIBUTES << " attributes | "
       << setw(10) << fixed << setprecision(2) << avg_accuracy_top3_ig << " %     | "
       << setw(8) << fixed << setprecision(2) << avg_accuracy_top3_gini << " %    | "
       << setw(10) << fixed << setprecision(2) << std_dev_top3_ig << "       | "
       << setw(8) << fixed << setprecision(2) << std_dev_top3_gini << "      | "
       << setw(10) << fixed << setprecision(2) << cv_top3_ig << "       | "
       << setw(9) << fixed << setprecision(2) << cv_top3_gini << "     |" << endl;    
  cout << "+-------------------------------------------+------------------+---------------+------------------+---------------+------------------+---------------+" << endl;
}

double
calculate_standard_deviation(vector<double>& accuracies)
{
  double mean = calculate_average(accuracies);
  double sum = 0.0;
  for(const auto& accuracy : accuracies)
  {
    sum += pow(accuracy - mean, 2);
  }
  return sqrt(sum / accuracies.size());
}

double
calculate_coefficient_of_variation(vector<double>& accuracies)
{
  double mean = calculate_average(accuracies);
  double standard_deviation = calculate_standard_deviation(accuracies);
  if (mean == 0)
    throw runtime_error("Mean is zero, coefficient of variation cannot be calculated.");
  return (standard_deviation / mean) * 100.0;
}

void
write_accuracies_and_times_to_csv(
  vector<double>& accuracies_best_ig, 
  vector<double>& accuracies_top3_ig, 
  vector<double>& accuracies_best_gini, 
  vector<double>& accuracies_top3_gini,
  vector<double>& training_times_best_ig,
  vector<double>& training_times_top3_ig,
  vector<double>& training_times_best_gini,
  vector<double>& training_times_top3_gini
)
{
  ofstream file(METRICS_FILE);
  if(!file.is_open())
    throw runtime_error("Could not open file: " + string(METRICS_FILE));
  file << "Run, Accuracy (Best IG), Accuracy (Top 3 IG), Accuracy (Best Gini), Accuracy (Top 3 Gini), "
          << "Training Time (Best IG), Training Time (Top 3 IG), Training Time (Best Gini), Training Time (Top 3 Gini)" << endl;
  int runs = accuracies_best_ig.size();
  for(int i = 0; i < runs; ++i)
  {
    file << i + 1 << ","
        << accuracies_best_ig[i] << ","
        << accuracies_top3_ig[i] << ","
        << accuracies_best_gini[i] << ","
        << accuracies_top3_gini[i] << ","
        << training_times_best_ig[i] << ","
        << training_times_top3_ig[i] << ","
        << training_times_best_gini[i] << ","
        << training_times_top3_gini[i] << endl;
  }
}

void
print_tree(const shared_ptr<TreeBuilder>& tree_builder, const string& file_path)
{
  ofstream file(file_path);
  if(file.is_open())
  {
    file << *tree_builder;
    file.close();
  }
  else
  {
    throw runtime_error("Could not open file: " + file_path);
  }
}