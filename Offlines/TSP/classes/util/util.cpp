#include "util.hpp"

void print_usage(const char* programName) {
    cout << "Usage: " << programName << " [-i <input_dir> | -f <input_file>] [-o <output_dir>] [-h]\n";
    cout << "Options:\n";
    cout << "  -i <input_dir>    Specify the input directory.\n";
    cout << "  -f <input_file>   Specify the input file.\n";
    cout << "  -o <output_dir>   Specify the output directory.\n";
    cout << "  -h                Display this help message.\n";
}

bool check_directory(const string& dirPath) {
    return fs::exists(dirPath) && fs::is_directory(dirPath);
}

void create_or_clear_directory(const string& dirPath) {
    if (fs::exists(dirPath)) {
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            fs::remove_all(entry.path());
        }
    } else {
        fs::create_directories(dirPath);
    }
}

bool parse_arguments(int argc, char* argv[], string& inputDir, string& inputFile, string& outputDir) {
    int opt;
    while ((opt = getopt(argc, argv, "i:f:o:h")) != -1) {
        switch (opt) {
            case 'i':
                if (!inputFile.empty()) {
                    cerr << "Error: -i and -f cannot be used together.\n";
                    print_usage(argv[0]);
                    return false;
                }
                inputDir = optarg;
                break;
            case 'f':
                if (!inputDir.empty()) {
                    cerr << "Error: -f and -i cannot be used together.\n";
                    print_usage(argv[0]);
                    return false;
                }
                inputFile = optarg;
                break;
            case 'o':
                outputDir = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                return false;
            default:
                print_usage(argv[0]);
                return false;
        }
    }
    if (inputDir.empty() && inputFile.empty()) {
        cerr << "Error: Either -i or -f must be specified.\n";
        print_usage(argv[0]);
        return false;
    }
    return true;
}

bool has_valid_ext(const string& filename, const string& extension) {
    return fs::path(filename).extension() == extension;
}