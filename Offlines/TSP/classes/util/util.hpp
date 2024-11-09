#pragma once

#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

void print_usage(const char*);
bool check_directory(const string&);
void create_or_clear_directory(const string&);
bool parse_arguments(int, char* [], string&, string&, string&);
bool has_valid_ext(const string&, const string&);
void write_csv(const string& file_path, const string& graph_name, const string& heuristic_name, const vector<int>&, long double, long double);
