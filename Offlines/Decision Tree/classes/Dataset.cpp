#include "Dataset.hpp"

pair<Dataset, Dataset> Dataset::split(double ratio)
{
  Dataset train, test;
  int total_size = dataset.size();
  int train_size = static_cast<int>(total_size * ratio);

  random_device rd;
  mt19937 gen(rd());
  shuffle(dataset.begin(), dataset.end(), gen);

  train.dataset.reserve(train_size);
  test.dataset.reserve(total_size - train_size);

  for (int i = 0; i < train_size; ++i)
  {
    train.dataset.push_back(dataset[i]);
  }
  for (int i = train_size; i < total_size; ++i)
  {
    test.dataset.push_back(dataset[i]);
  }

  return {train, test};
}

istream& operator>>(istream& in, Dataset& d)
{
  string line;
  while (getline(in, line))
  {
    stringstream ss(line);
    vector<string> row;
    string value;
    while (getline(ss, value, ','))
    {
      row.push_back(value);
    }
    d.dataset.push_back(row);
  }
  return in;
}

ostream& operator<<(ostream& out, const Dataset& d)
{
  if (d.dataset.empty()) return out;

  // Print the top border
  out << "+";
  for (size_t i = 0; i < d.dataset[0].size(); ++i) {
    out << "-------+"; // Column width with border
  }
  out << "\n";

  // Print the rows with borders
  for (const auto& row : d.dataset)
  {
    out << "|";
    for (size_t i = 0; i < row.size(); ++i)
    {
      out << " " << setw(5) << left << row[i] << " |"; // Adjust width as necessary
    }
    out << "\n";

    // Print row separator border
    out << "+";
    for (size_t i = 0; i < row.size(); ++i) {
      out << "-------+"; // Column width with border
  }
    out << "\n";
  }

  return out;
}

vector<vector<string>>
Dataset::get_dataset() const
{
  return dataset;
}