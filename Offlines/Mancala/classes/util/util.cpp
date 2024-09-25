#include "util.hpp"

int validate_move(string move) {
    for (char c : move) {
        if (!isdigit(c)) {
            return -1;
        }
    }
    return stoi(move);
}