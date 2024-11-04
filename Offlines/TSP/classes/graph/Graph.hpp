#pragma once

#include <bits/stdc++.h>

using namespace std;

class Graph {
    string name;
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
};