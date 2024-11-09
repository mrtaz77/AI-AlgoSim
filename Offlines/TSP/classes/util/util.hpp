#pragma once

#include <bits/stdc++.h>
#include <unistd.h>
#include "../graph/Graph.hpp"
#include "../tsp/TSP.hpp"
#include "../tsp/heuristics/Heuristics.hpp"
#include "../tsp/heuristics/constructive/Versions.hpp"

using namespace std;
namespace fs = filesystem;

void print_usage(const char*);
bool check_directory(const string&);
void create_or_clear_directory(const string&);
bool parse_arguments(int, char* [], string&, string&, string&);
bool has_valid_ext(const string&, const string&);
void write_csv(const string&, const string&, const string&, const string&, const vector<int>&, long double, long double);
void process_graph_with_heuristic_version(Graph&, const string&, Heuristics, Versions);
void process_all_versions(Graph&, const string&, Heuristics);
void load_graphs_from_directory(const string&, vector<Graph>&);
