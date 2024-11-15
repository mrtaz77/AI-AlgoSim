#include "MST.hpp"

MST::MST(Graph& graph) : Constructive(graph) {}

void MST::solve() {
    auto start = chrono::high_resolution_clock::now();

    size_t num_vertices = g.get_number_of_vertices();
    tour.clear();
    tour.reserve(num_vertices + 1);

    vector<int> parent(num_vertices, -1);
    vector<long double> minimum_edge_cost(num_vertices, numeric_limits<long double>::max());
    vector<bool> in_mst(num_vertices, false);

    priority_queue<pair<long double, int>, vector<pair<long double, int>>, greater<>> pq;

    pq.push({0, 0});
    minimum_edge_cost[0] = 0;

    while(!pq.empty()) {
        size_t u = pq.top().second;
        pq.pop();

        if(in_mst[u]) continue;
        in_mst[u] = true;

        for(size_t v = 0; v < num_vertices; ++v) {
            if(u != v && !in_mst[v]) {
                long double weight = g.get_edge_weight(u, v);
                if (weight < minimum_edge_cost[v]) {
                    minimum_edge_cost[v] = weight;
                    pq.push({weight, v});
                    parent[v] = u;
                }
            }
        }
    }

    auto mst_adj = build_mst(parent);

    vector<bool> visited(num_vertices, false);
    dfs(starting_node, visited, mst_adj);

    tour.push_back(tour[0]);

    auto end = chrono::high_resolution_clock::now();
    time_taken = chrono::duration<double>(end - start).count();

    compute_tour_cost();
}

const string MST::get_heuristic_name() const { return "Minimum Spanning Tree"; }

bool MST::is_start_variable() { return true; }

vector<vector<int>> MST::build_mst(const vector<int>& parent) {
    vector<vector<int>> mst_adj(g.get_number_of_vertices());
    for (int v = 1; v < g.get_number_of_vertices(); ++v) {
        int u = parent[v];
        if (u != -1) {
            mst_adj[u].push_back(v);
            mst_adj[v].push_back(u);
        }
    }
    return mst_adj;  // Returning by value avoids the warning
}

void MST::dfs(int node, vector<bool>& visited, vector<vector<int>>& mst) {
    visited[node] = true;
    tour.push_back(node);
    for(int neighbor : mst[node]) {
        if(!visited[neighbor]) dfs(neighbor, visited, mst);
    }
}