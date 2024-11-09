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

    if (!inputDir.empty()) {
        vector<Graph> graphs;
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            if (entry.is_regular_file() && has_valid_ext(entry.path().string(), ".tsp")) {
                ifstream inputFile(entry.path());
                if (!inputFile) {
                    cerr << "Error: Unable to open file " << entry.path() << "\n";
                    continue;
                }

                Graph g;
                inputFile >> g;
                graphs.push_back(g);

                TSP tsp(g);

                tsp.set_graph(g);
                tsp.set_heuristic(Heuristics::NEAREST_NEIGHBOUR);
                tsp.run();

                const auto& tour = tsp.get_tour();
                auto cost = tsp.get_cost();
                auto time = tsp.get_time();

                string csvFilePath = outputDir + "/" + entry.path().stem().string() + ".csv";
                write_csv(csvFilePath, g.get_name(), "Nearest Neighbour", tour, cost, time);
            }
        }
    }

    if (!inputFile.empty()) {
        if (!has_valid_ext(inputFile, ".tsp")) {
            cerr << "Error: Invalid file extension for " << inputFile << ". Only .tsp files are valid.\n";
            return 1;
        }

        ifstream inputFileStream(inputFile);
        if (!inputFileStream) {
            cerr << "Error: Unable to open file " << inputFile << "\n";
            return 1;
        }

        Graph g;
        inputFileStream >> g;

        TSP tsp(g);

        tsp.set_graph(g);
        tsp.set_heuristic(Heuristics::NEAREST_NEIGHBOUR);
        tsp.run();

        const auto& tour = tsp.get_tour();
        auto cost = tsp.get_cost();
        auto time = tsp.get_time();

        string csvFilePath = outputDir + "/" + fs::path(inputFile).stem().string() + ".csv";
        write_csv(csvFilePath, g.get_name(), "Nearest Neighbour", tour, cost, time);
    }

    return 0;
}
