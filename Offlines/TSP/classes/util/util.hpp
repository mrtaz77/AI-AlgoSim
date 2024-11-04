#pragma once

#include <bits/stdc++.h>

using namespace std;
namespace fs = filesystem;

void print_usage(const char*);
bool check_directory(const string&);
void create_or_clear_directory(const string&);
bool parse_arguments(int, char* [], string&, string&, string&);
bool has_valid_ext(const string&, const string&);
