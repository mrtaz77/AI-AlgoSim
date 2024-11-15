#include "util.hpp"

void print_usage(const char* program_name) {
    cout << "Usage: " << program_name << " [-i <input_dir> | -f <input_file>] [-o <output_file>] [-h]\n";
    cout << "Options:\n";
    cout << "  -i <input_dir>    Specify the input directory.\n";
    cout << "  -f <input_file>   Specify the input file.\n";
    cout << "  -o <output_file>  Specify the output file.\n";
    cout << "  -h                Display this help message.\n";
}

bool check_directory(const string& dir_path) {
    return fs::exists(dir_path) && fs::is_directory(dir_path);
}

bool parse_arguments(int argc, char* argv[], string& input_dir, string& input_file, string& output_file) {
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
                output_file = optarg;
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

void generate_tsp_with_heuristics_and_version(TSP& tsp, Heuristics constructive_heuristic_type, Heuristics perturbative_heuristic_type, Versions version) {
    tsp.set_heuristics(constructive_heuristic_type, perturbative_heuristic_type);
    tsp.set_version(version);
    tsp.run();
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

void generate_tsp_tours(Graph& graph, const string& output_file) {
    TSP tsp(graph);
    vector<Versions> versions = {Versions::GREEDY, Versions::SEMI_GREEDY_3, Versions::SEMI_GREEDY_5};
    vector<Heuristics> constructive_heuristics = {Heuristics::NEAREST_NEIGHBOUR, Heuristics::FARTHEST_INSERTION, Heuristics::MINIMUM_SPANNING_TREE}; 
    vector<Heuristics> perturbative_heuristics = {Heuristics::NODE_SHIFT, Heuristics::TWO_OPT};
    bool new_constructive_heuristics = false;
    for (auto version : versions) {
        for (auto constructive_heuristic : constructive_heuristics) {
            new_constructive_heuristics = true;
            for (auto perturbative_heuristic : perturbative_heuristics) {
                generate_tsp_with_heuristics_and_version(tsp, constructive_heuristic, perturbative_heuristic, version);
                write_to_file(output_file, tsp, new_constructive_heuristics);
                new_constructive_heuristics = false;
            }
        }
    }
}

void write_to_file(const string& output_file, const TSP& tsp, bool new_constructive_heuristics) {
    ofstream file(output_file + ".csv", ios::app);
    if (!file) {
        cerr << "Error: Unable to open file " << output_file << " for writing.\n";
        exit(1);
    }
    
    string version = (tsp.get_version() == Versions::GREEDY) ? "Greedy" :
                    (tsp.get_version() == Versions::SEMI_GREEDY_3) ? "Semi-Greedy 3" : "Semi-Greedy 5";
    file << fixed << setprecision(3);
    if(new_constructive_heuristics) {
        file << tsp.get_graph().get_filename() << "," << tsp.get_graph().get_name() << ","
            << version << "," << tsp.get_heuristic_name(Heuristics::CONSTRUCTIVE) << ","
            << tsp.get_best_cost(Heuristics::CONSTRUCTIVE) << "," 
            << tsp.get_avg_cost(Heuristics::CONSTRUCTIVE) << "," 
            << tsp.get_worst_cost(Heuristics::CONSTRUCTIVE) << ","
            << tsp.get_best_time(Heuristics::CONSTRUCTIVE) * 1'000'000 << ","
            << tsp.get_avg_time(Heuristics::CONSTRUCTIVE) * 1'000'000 << ","
            << tsp.get_worst_time(Heuristics::CONSTRUCTIVE) * 1'000'000 << endl;
    }
    file << tsp.get_graph().get_filename() << "," << tsp.get_graph().get_name() << ","
        << version << "," << tsp.get_heuristic_name(Heuristics::CONSTRUCTIVE) << "+" << tsp.get_heuristic_name(Heuristics::PERTURBATIVE) << ","
        << tsp.get_best_cost(Heuristics::PERTURBATIVE) << "," 
        << tsp.get_avg_cost(Heuristics::PERTURBATIVE) << "," 
        << tsp.get_worst_cost(Heuristics::PERTURBATIVE) << ","
        << tsp.get_best_time(Heuristics::PERTURBATIVE) * 1'000'000 << ","
        << tsp.get_avg_time(Heuristics::PERTURBATIVE) * 1'000'000 << ","
        << tsp.get_worst_time(Heuristics::PERTURBATIVE) * 1'000'000 << endl;
    file.close();
}

void initialize_output_file(const string& output_file) {
    ofstream file(output_file + ".csv");
    if (!file) {
        cerr << "Error: Unable to open file " << output_file << " for writing.\n";
        exit(1);
    }
    file << "Graph File,Graph Name," 
        << "Version,Heuristic,"
        << "Best Cost,Avg Cost,Worst Cost,"
        << "Best Time (µs),Avg Time (µs),Worst Time (µs)" << endl;
    file.close();
}

void show_progress(int current, int total) {
    const int bar_width = 50;
    float progress = float(current) / total;
    
    cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos)
            cout << "=";
        else if (i == pos)
            cout << ">";
        else
            cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r"; // Carriage return to overwrite the line
    cout.flush();
}
