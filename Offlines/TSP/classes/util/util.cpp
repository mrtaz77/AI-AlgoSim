#include "util.hpp"

void print_usage(const char* program_name) {
    cout << "Usage: " << program_name << " [-i <input_dir> | -f <input_file>] [-o <output_dir>] [-h]\n";
    cout << "Options:\n";
    cout << "  -i <input_dir>    Specify the input directory.\n";
    cout << "  -f <input_file>   Specify the input file.\n";
    cout << "  -o <output_dir>   Specify the output directory.\n";
    cout << "  -h                Display this help message.\n";
}

bool check_directory(const string& dir_path) {
    return fs::exists(dir_path) && fs::is_directory(dir_path);
}

void create_or_clear_directory(const string& dir_path) {
    if (fs::exists(dir_path)) {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            fs::remove_all(entry.path());
        }
    } else {
        fs::create_directories(dir_path);
    }
}

bool parse_arguments(int argc, char* argv[], string& input_dir, string& input_file, string& output_dir) {
    int opt;
    while ((opt = getopt(argc, argv, "i:f:o:h")) != -1) {
        switch (opt) {
            case 'i':
                if (!input_file.empty()) {
                    cerr << "Error: -i and -f cannot be used together.\n";
                    print_usage(argv[0]);
                    return false;
                }
                input_dir = optarg;
                break;
            case 'f':
                if (!input_dir.empty()) {
                    cerr << "Error: -f and -i cannot be used together.\n";
                    print_usage(argv[0]);
                    return false;
                }
                input_file = optarg;
                break;
            case 'o':
                output_dir = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                return false;
            default:
                print_usage(argv[0]);
                return false;
        }
    }
    if (input_dir.empty() && input_file.empty()) {
        cerr << "Error: Either -i or -f must be specified.\n";
        print_usage(argv[0]);
        return false;
    }
    return true;
}

bool has_valid_ext(const string& file_name, const string& extension) {
    return fs::path(file_name).extension() == extension;
}

void write_csv(const string& file_path, 
            const string& graph_name,
            const string& version_name,
            const string& heuristic_name, 
            const vector<int>& tour, 
            long double cost, 
            long double time) {
    ofstream file(file_path, ios::app);
    bool new_file = file.tellp() == 0;
    
    if (!file) {
        cerr << "Error: Unable to open file " << file_path << " for writing.\n";
        return;
    }

    if (new_file) {
        file << "Graph Name,Version,Heuristic,Tour,Cost,Time\n";
    }

    file << graph_name << ",";
    file << version_name << ",";
    file << heuristic_name << ",";

    for (size_t i = 0; i < tour.size(); ++i) {
        file << tour[i];
        if (i < tour.size() - 1) {
            file << "-";
        }
    }
    file << ",";

    file << fixed << setprecision(2) << cost << ",";
    file << fixed << setprecision(4) << time * 1000 << "ms\n";
}

void process_graph_with_heuristic_version(Graph& graph, const string& output_dir, Heuristics heuristic_type, Versions version) {
    TSP tsp(graph);
    tsp.set_heuristic(heuristic_type);
    tsp.set_version(version);
    tsp.run();

    const auto& tour = tsp.get_tour();
    auto cost = tsp.get_cost();
    auto time = tsp.get_time();

    string heuristic_name = (heuristic_type == Heuristics::NEAREST_NEIGHBOUR) ? "Nearest Neighbour" : "Unknown";
    string version_name = (version == Versions::GREEDY) ? "Greedy" : (version == Versions::SEMI_GREEDY_3) ? "Semi-Greedy-3" : "Semi-Greedy-5";
    string csv_file_path = output_dir + "/" + graph.get_filename() + ".csv";

    write_csv(csv_file_path, graph.get_name(), version_name, heuristic_name, tour, cost, time);
}

void load_graphs_from_directory(const string& input_dir, vector<Graph>& graphs) {
    for (const auto& entry : fs::directory_iterator(input_dir)) {
        if (entry.is_regular_file() && has_valid_ext(entry.path().string(), ".tsp")) {
            ifstream input_file(entry.path());
            if (!input_file) {
                cerr << "Error: Unable to open file " << entry.path() << "\n";
                continue;
            }
            Graph g;
            input_file >> g;
            graphs.push_back(g);
        }
    }
}

void process_all_versions(Graph& g, const string& outputDir, Heuristics heuristicType) {
    vector<Versions> versions = {Versions::GREEDY, Versions::SEMI_GREEDY_3, Versions::SEMI_GREEDY_5};

    for (const auto version : versions) {
        process_graph_with_heuristic_version(g, outputDir, heuristicType, version);
    }
}