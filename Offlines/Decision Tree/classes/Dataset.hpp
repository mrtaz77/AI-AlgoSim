#pragma once

#include <bits/stdc++.h>

using namespace std;

class Dataset
{
  vector<vector<string>> dataset;
public:
  pair<Dataset, Dataset> split(double);
  friend istream& operator>>(istream&, Dataset&);
  friend ostream& operator<<(ostream&, const Dataset&);
  vector<vector<string>> get_dataset() const;
};