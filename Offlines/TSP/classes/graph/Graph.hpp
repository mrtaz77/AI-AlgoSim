#pragma once

#include <bits/stdc++.h>

using namespace std;

class Graph {
    string name;
    string filename;
    vector<vector<long double>> graph;
    int number_of_vertices;
    vector<std::pair<long double, long double>> coordinates;
    long double euclidean_distance(int, int);
    void initialize_graph();
public:
    Graph();
    ~Graph();
    friend istream& operator>>(istream&, Graph&);
    friend ostream& operator<<(ostream& , const Graph&);
    int get_number_of_vertices() const;
    long double get_edge_weight(int, int) const;
    const string& get_name() const;
    void set_filename(const string&);
    const string& get_filename() const;
};