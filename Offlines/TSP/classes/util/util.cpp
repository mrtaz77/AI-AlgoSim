#include "util.hpp"

void print_usage(const char* programName) {
    cout << "Usage: " << programName << " [-i <input_dir> | -f <input_file>] [-o <output_dir>] [-h]\n";
    cout << "Options:\n";
    cout << "  -i <input_dir>    Specify the input directory.\n";
    cout << "  -f <input_file>   Specify the input file.\n";
    cout << "  -o <output_dir>   Specify the output directory.\n";
    cout << "  -h                Display this help message.\n";
}