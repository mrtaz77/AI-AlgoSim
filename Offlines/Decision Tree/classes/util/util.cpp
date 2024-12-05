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

  auto ig = make_shared<InformationGain>();
  auto gini = make_shared<GiniImpurity>();
  auto best = make_shared<BestAttribute>();
  auto random_top = make_shared<RandomTopAttribute>(MAX_TOP_ATTRIBUTES);

  for(int i = 0; i < runs; i++)
  {
    auto [train, test] = dataset.split(TRAINING_SPLIT_RATIO);

    auto train_set = train.get_dataset();
    auto test_set = test.get_dataset();

    auto tree_builder = make_shared<TreeBuilder>(ig, best);
    tree_builder->build_tree(train_set);
    accuracies_best_ig.push_back(tree_builder->calculate_accuracy(test_set));

    tree_builder->set_attribute(random_top);
    tree_builder->build_tree(train_set);
    accuracies_top3_ig.push_back(tree_builder->calculate_accuracy(test_set));

    tree_builder->set_heuristic(gini);
    tree_builder->build_tree(train_set);
    accuracies_top3_gini.push_back(tree_builder->calculate_accuracy(test_set));

    tree_builder->set_attribute(best);
    tree_builder->build_tree(train_set);
    accuracies_best_gini.push_back(tree_builder->calculate_accuracy(test_set));
  }

  statistics(accuracies_best_ig, accuracies_top3_ig, accuracies_best_gini, accuracies_top3_gini);
  write_accuracies_to_csv(accuracies_best_ig, accuracies_top3_ig, accuracies_best_gini, accuracies_top3_gini);
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
  cout << "|              # of Runs = " << runs << "               |         Average accuracy         |        Standard Deviation        |     Co-efficient of Variation    |" << endl;
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
write_accuracies_to_csv(vector<double>& accuracies_best_ig, vector<double>& accuracies_top3_ig, vector<double>& accuracies_best_gini, vector<double>& accuracies_top3_gini)
{
  ofstream file(ACCURACY_FILE);
  if(!file.is_open())
    throw runtime_error("Could not open file: " + string(ACCURACY_FILE));
  file << "Run,Heuristic,Attribute,Accuracy\n";
  int runs = accuracies_best_ig.size();
  for(int i = 0; i < runs; ++i)
  {
    file << i + 1 << ",Information Gain,Best," << accuracies_best_ig[i] << "\n";
    file << i + 1 << ",Information Gain,Random Top 3," << accuracies_top3_ig[i] << "\n";
    file << i + 1 << ",Gini Impurity,Best," << accuracies_best_gini[i] << "\n";
    file << i + 1 << ",Gini Impurity,Random Top 3," << accuracies_top3_gini[i] << "\n";
  }
}