#include <iostream>
#include <string>
#include <filesystem>
#include "classes/util/util.hpp"

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
        cout << "Input Directory: " << inputDir << "\n";
    }
    
    if (!inputFile.empty()) {
        cout << "Input File: " << inputFile << "\n";
    }
    if (!outputDir.empty()) {
        cout << "Output Directory: " << outputDir << "\n";
    }

    return 0;
}
