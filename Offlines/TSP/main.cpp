#include <iostream>
#include <string>
#include "classes/util/util.hpp"
#include "classes/graph/Graph.hpp"

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

                string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".txt";
                ofstream outputFile(outputFilePath);
                if (outputFile) {
                    outputFile << g;
                } else {
                    cerr << "Error: Unable to open output file " << outputFilePath << "\n";
                }
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

        string outputFilePath = outputDir + "/" + fs::path(inputFile).stem().string() + ".txt";
        ofstream outputFile(outputFilePath);
        if (outputFile) {
            outputFile << g;
        } else {
            cerr << "Error: Unable to open output file " << outputFilePath << "\n";
        }
    }

    return 0;
}
