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
bool parse_arguments(int, char* [], string&, string&, string&);
bool has_valid_ext(const string&, const string&);
void generate_tsp_with_heuristics_and_version(TSP&, Heuristics, Heuristics, Versions);
void generate_tsp_tours(Graph&, const string&);
void load_graphs_from_directory(const string&, vector<Graph>&);
void write_to_file(const string&, const TSP&, bool);
void initialize_output_file(const string& output_file);
void show_progress(int, int);