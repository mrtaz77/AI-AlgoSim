#include "GameSnapshot.hpp"

GameSnapshot::GameSnapshot() {
    board = vector<int>(BOARD_SIZE, INITIAL_NUM_OF_STONES_PER_BIN);
    board[6] = board[13] = 0;
    is_turn_of_A = true;
}

ostream& operator<<(ostream& out, const GameSnapshot& snapshot) {
    out << "+-----+-----+-----+-----+-----+-----+-----+-----+\n";
    out << "| ";
    for (int i = 13; i >= 7; --i) {
        out << std::setw(2) << snapshot.board[i] << "  | ";
    }
    out << " A  |";
    out << "\n+     +-----+-----+-----+-----+-----+-----+     +\n";
    out << "|  B  | ";
    for (int i = 0; i <= 6; ++i) {
        out << std::setw(2) << snapshot.board[i] << "  | ";
    }
    out << "\n+-----+-----+-----+-----+-----+-----+-----+-----+\n";
    return out;
}

