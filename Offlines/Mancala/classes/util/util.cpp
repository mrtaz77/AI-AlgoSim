#include "util.hpp"

int validate_move(string move) {
    for (char c : move) {
        if (!isdigit(c)) {
            return -1;
        }
    }
    return stoi(move);
}

enum Modes validate_choice(string choice) {
    for (char c : choice) {
        if (!isdigit(c)) {
            return Modes::INVALID;
        }
    }
    switch(stoi(choice)) {
        case 0:
            return Modes::PLAYER_VS_PLAYER;
        case 1:
            return Modes::PLAYER_VS_AI;
        case 2:
            return Modes::AI_VS_AI;
        default:
            return Modes::INVALID;
    }
}