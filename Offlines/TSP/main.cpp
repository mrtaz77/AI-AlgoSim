#include <iostream>
#include <string>
#include "classes/util/util.hpp"
#include "classes/graph/Graph.hpp"
#include "classes/tsp/TSP.hpp"
#include "classes/tsp/heuristics/Heuristics.hpp"

int main(int argc, char* argv[]) {
    string input_dir, input_file, output_file;

    if (!parse_arguments(argc, argv, input_dir, input_file, output_file)) {
        return 1;
    }

    if (!input_dir.empty() && !check_directory(input_dir)) {
        cerr << "Error: Specified input directory does not exist.\n";
        return 1;
    }

    if (!output_file.empty()) {
        initialize_output_file(output_file);
    }

    vector<Graph> graphs;

    if (!input_dir.empty()) {
        load_graphs_from_directory(input_dir, graphs);
        int total_graphs = graphs.size();
        int current = 0;
        for (auto& g : graphs) {
            generate_tsp_tours(g, output_file);
            show_progress(++current, total_graphs);
        }
    }

    if (!input_file.empty()) {
        if (!has_valid_ext(input_file, ".tsp")) {
            cerr << "Error: Invalid file extension for " << input_file << ". Only .tsp files are valid.\n";
            return 1;
        }

        ifstream inputFileStream(input_file);
        if (!inputFileStream) {
            cerr << "Error: Unable to open file " << input_file << "\n";
            return 1;
        }

        Graph g;
        inputFileStream >> g;
        generate_tsp_tours(g, output_file);
    }

    return 0;
}
