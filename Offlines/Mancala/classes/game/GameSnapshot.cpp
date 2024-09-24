#include "GameSnapshot.hpp"

GameSnapshot::GameSnapshot() {
    board = vector<int>(BOARD_SIZE, INITIAL_NUM_OF_STONES_PER_BIN);
    board[NUM_OF_BINS_PER_SIDE] = board[BOARD_SIZE - 1] = 0;
    current_turn = make_unique<PlayerATurn>();
}

ostream& operator<<(ostream& out, const GameSnapshot& game_snap) {
    out << "+-----+-----+-----+-----+-----+-----+-----+-----+\n";
    out << "| ";
    for (int i = 13; i >= 7; --i) {
        out << std::setw(2) << game_snap.board[i] << "  | ";
    }
    out << " A  |";
    out << "\n+     +-----+-----+-----+-----+-----+-----+     +\n";
    out << "|  B  | ";
    for (int i = 0; i <= 6; ++i) {
        out << std::setw(2) << game_snap.board[i] << "  | ";
    }
    out << "\n+-----+-----+-----+-----+-----+-----+-----+-----+\n";
    return out;
}

void GameSnapshot::make_move(int pitIndex) {
    current_turn->make_move(*this, pitIndex);
}

bool GameSnapshot::is_playerA_turn() const {
    return dynamic_cast<PlayerATurn*>(current_turn.get()) != nullptr;
}

bool GameSnapshot::is_game_over() const {
    int sumA = 0, sumB = 0;
    for (int i = 0; i < NUM_OF_BINS_PER_SIDE; ++i) {
        sumA += board[i];
        sumB += board[i + NUM_OF_BINS_PER_SIDE + 1];
    }
    return sumA == 0 || sumB == 0;
}

int GameSnapshot::get_stones_in_bin(int bin_index) {
    return board[bin_index];
}

int GameSnapshot::get_storageA() const {
    return board[NUM_OF_BINS_PER_SIDE];
}

int GameSnapshot::get_storageB() const {
    return board[BOARD_SIZE - 1];
}

void GameSnapshot::set_stones_in_bin(int bin_index, int stones) {
    board[bin_index] = stones;
}

void GameSnapshot::set_turn(unique_ptr<Turn> turn) {
    current_turn = move(turn);
}