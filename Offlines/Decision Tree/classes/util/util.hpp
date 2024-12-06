#pragma once

#include "../Dataset.hpp"
#include "../validator/ColumnValidator.hpp"
#include "../validator/FileExists.hpp"
#include "../validator/RowValidator.hpp"
#include "../validator/Validator.hpp"
#include "../TrainTestConstants.hpp"
#include "../TreeBuilder.hpp"
#include "../attribute/BestAttribute.hpp"
#include "../attribute/RandomTopAttribute.hpp"
#include "../heuristic/InformationGain.hpp"
#include "../heuristic/GiniImpurity.hpp"
#include "../ReportConstants.hpp"

using namespace std;
namespace fs = filesystem;

void validate_args(int argc, char *argv[], string&, int&);
void validate_file(const string&);
Dataset load_dataset(const string&);
void train_and_test(Dataset&, int);
double calculate_average(vector<double>&);
void statistics(vector<double>&,vector<double>&,vector<double>&,vector<double>&);
double calculate_standard_deviation(vector<double>&);
double calculate_coefficient_of_variation(vector<double>&);
void write_accuracies_and_times_to_csv(
  vector<double>&,vector<double>&,vector<double>&,vector<double>&,
  vector<double>&,vector<double>&,vector<double>&,vector<double>&
);
void print_tree(const shared_ptr<TreeBuilder>&, const string&);