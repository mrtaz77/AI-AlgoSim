#include "util.hpp"

int validate_move(string move) {
    for (char c : move) {
        if (!isdigit(c)) {
            return -1;
        }
    }
    return stoi(move);
}

Modes validate_mode_choice(string choice) {
    for (char c : choice) {
        if (!isdigit(c)) {
            return Modes::INVALID;
        }
    }
    switch(stoi(choice)) {
        case 1:
            return Modes::HUMAN_VS_HUMAN;
        case 2:
            return Modes::HUMAN_VS_AI;
        case 3:
            return Modes::AI_VS_AI;
        default:
            return Modes::INVALID;
    }
}

Heuristics validate_heuristic_choice(string choice) {
    for (char c : choice) {
        if (!isdigit(c)) {
            return Heuristics::INVALID;
        }
    }
    switch(stoi(choice)) {
        case 1:
            return Heuristics::H1;
        case 2:
            return Heuristics::H2;
        case 3:
            return Heuristics::H3;
        case 4:
            return Heuristics::H4;
        default:
            return Heuristics::INVALID;
    }
}