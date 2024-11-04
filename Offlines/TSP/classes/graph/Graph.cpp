#include "Graph.hpp"

Graph::Graph() {
    name = "";
    number_of_vertices = 0;
}

Graph::~Graph() {
    graph.clear();
    number_of_vertices = 0;
}

istream& operator>>(istream& is, Graph& g) {
    string line;
    int dimension = 0;

    while (getline(is, line)) {
        if (line.find("COMMENT") != string::npos) {
            g.name = line.substr(line.find(":") + 2);
        } else if (line.find("DIMENSION") != string::npos) {
            dimension = stoi(line.substr(line.find(':') + 2));
            g.number_of_vertices = dimension;
            g.coordinates.resize(dimension);
            g.initialize_graph();
        } else if (line.find("NODE_COORD_SECTION") != string::npos) {
            for (int i = 0; i < dimension; ++i) {
                getline(is, line);
                istringstream iss(line);
                int index;
                long double x, y;
                iss >> index >> x >> y;
                g.coordinates[index - 1] = {x, y};
            }
        }
    }

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (i != j) {
                g.graph[i][j] = g.euclidean_distance(i, j);
            }
        }
    }

    return is;
}

long double Graph::euclidean_distance(int index1, int index2) {
    long double x1 = coordinates[index1].first;
    long double y1 = coordinates[index1].second;
    long double x2 = coordinates[index2].first;
    long double y2 = coordinates[index2].second;

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Graph::initialize_graph() {
    graph.resize(number_of_vertices, vector<long double>(number_of_vertices, numeric_limits<long double>::max()));

    for (int i = 0; i < number_of_vertices; i++) {
        graph[i][i] = 0;
    }
}

ostream& operator<<(ostream& out, const Graph& g) {
    out << g.name << " " <<  g.number_of_vertices << " x " << g.number_of_vertices << "\n"; // Print dimensions
    for (int i = 0; i < g.number_of_vertices; ++i) {
        for (int j = 0; j < g.number_of_vertices; ++j) {
            if (g.graph[i][j] == numeric_limits<long double>::max()) {
                out << "INF";
            } else {
                out << fixed << setprecision(2) << g.graph[i][j];
            }
            if (j < g.number_of_vertices - 1) {
                out << " ";
            }
        }
        out << "\n";
    }
    return out;
}

int Graph::get_number_of_vertices() const { return number_of_vertices; }

long double Graph::get_edge_weight(int i, int j) const { return graph[i][j]; }
