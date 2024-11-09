#include <iostream>
#include <string>
#include "classes/util/util.hpp"
#include "classes/graph/Graph.hpp"
#include "classes/tsp/TSP.hpp"
#include "classes/tsp/heuristics/Heuristics.hpp"

int main(int argc, char* argv[]) {
    string inputDir, inputFile, outputDir;

    if (!parse_arguments(argc, argv, inputDir, inputFile, outputDir)) {
        return 1;
    }

    if (!inputDir.empty() && !check_directory(inputDir)) {
        cerr << "Error: Specified input directory does not exist.\n";
        return 1;
    }

    if (!outputDir.empty()) {
        create_or_clear_directory(outputDir);
    }

    vector<Graph> graphs;

    if (!inputDir.empty()) {
        load_graphs_from_directory(inputDir, graphs);
        for (auto& g : graphs) {
            process_all_versions(g, outputDir, Heuristics::NEAREST_NEIGHBOUR);
        }
    }

    if (!inputFile.empty()) {
        if (!has_valid_ext(inputFile, ".tsp")) {
            std::cerr << "Error: Invalid file extension for " << inputFile << ". Only .tsp files are valid.\n";
            return 1;
        }

        std::ifstream inputFileStream(inputFile);
        if (!inputFileStream) {
            std::cerr << "Error: Unable to open file " << inputFile << "\n";
            return 1;
        }

        Graph g;
        inputFileStream >> g;
        process_all_versions(g, outputDir, Heuristics::NEAREST_NEIGHBOUR);
    }

    return 0;
}
