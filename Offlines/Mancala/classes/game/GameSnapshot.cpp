#include "GameSnapshot.hpp"

GameSnapshot::GameSnapshot() {
    board = vector<int>(BOARD_SIZE, INITIAL_NUM_OF_STONES_PER_BIN);
    board[NUM_OF_BINS_PER_SIDE] = board[BOARD_SIZE - 1] = 0;
    current_turn = make_unique<PlayerATurn>();
    playerA_additonal_moves = playerB_additonal_moves = 0;
    playerA_stones_captured = playerB_stones_captured = 0;
}

ostream& operator<<(ostream& out, const GameSnapshot& game_snap) {
    int n = NUM_OF_BINS_PER_SIDE; 
    // Top row of indices
    out << "+-----";
    for (int i = 0; i < n; ++i) out << "+-----";
    out << "+-----+\n";
    
    // Index of bins on the top row
    out << "|     | ";
    for (int i = 2 * n ; i > n; --i) {
        out << setw(2) << i << "  | ";
    }
    out << "    |";
    out << "\n+-----";
    for (int i = 0; i < n; ++i) out << "+-----";
    out << "+-----+\n";
    
    // Top row of bin contents (Player B's side)
    out << "| ";
    out << setw(2) << game_snap.get_storageB() << "  | ";  // Player B's storage at index 2n
    for (int i = 2 * n ; i > n; --i) {
        out << setw(2) << game_snap.board[i] << "  | ";
    }
    out << " A  |";
    out << "\n+     +";
    for (int i = 0; i < n; ++i) out << "-----+";
    out << "     +\n";
    
    // Bottom row of bin contents (Player A's side)
    out << "|  B  | ";
    for (int i = 0; i < n; ++i) {
        out << setw(2) << game_snap.board[i] << "  | ";
    }
    out << setw(2) << game_snap.get_storageA() << "  |";  // Player B's storage at index n
    out << "\n+-----";
    for (int i = 0; i < n; ++i) out << "+-----";
    out << "+-----+\n";
    
    // Bottom row of indices
    out << "|     | ";
    for (int i = 0; i < n; ++i) {
        out << setw(2) << i << "  | ";
    }
    out << "    |";
    out << "\n+-----";
    for (int i = 0; i < n; ++i) out << "+-----";
    out << "+-----+\n";
    
    return out;
}

void GameSnapshot::make_move(int bin_index) {
    if(current_turn->is_valid_turn(*this, bin_index)) current_turn->make_move(*this, bin_index);
}

bool GameSnapshot::is_playerA_turn() const {
    return dynamic_cast<PlayerATurn*>(current_turn.get()) != nullptr;
}

bool GameSnapshot::is_game_over() {
    int sumA = 0, sumB = 0;
    for (int i = 0; i < NUM_OF_BINS_PER_SIDE; ++i) {
        sumA += board[i];
        sumB += board[i + NUM_OF_BINS_PER_SIDE + 1];
    }
    if( sumA == 0 || sumB == 0 ) {
        finish_game(sumA, sumB);
        return true;
    }
    return false;
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

void GameSnapshot::change_turn() {
    if(is_playerA_turn()) current_turn = make_unique<PlayerBTurn>();
    else current_turn = make_unique<PlayerATurn>();
}

void GameSnapshot::finish_game(int sumA, int sumB){
    if(sumA == 0) board[BOARD_SIZE - 1] += sumB;
    else if(sumB == 0) board[NUM_OF_BINS_PER_SIDE] += sumA;
    for(int i = 0; i < NUM_OF_BINS_PER_SIDE; i++) {
        board[i] = 0;
        board[i + NUM_OF_BINS_PER_SIDE + 1] = 0;
    }
}

int GameSnapshot::get_stones_in_mancalaA() const {
    int stones = 0;
    for(int i = 0; i < NUM_OF_BINS_PER_SIDE; i++) stones+= board[i];
    return stones;
}

int GameSnapshot::get_stones_in_mancalaB() const {
    int stones = 0;
    for(int i = NUM_OF_BINS_PER_SIDE + 1; i < BOARD_SIZE - 1; i++) stones+= board[i];
    return stones;
}

int GameSnapshot::get_playerA_additional_moves() const {
    return playerA_additonal_moves;
}

int GameSnapshot::get_playerB_additional_moves() const {
    return playerB_additonal_moves;
}

void GameSnapshot::increment_playerA_additional_moves() {
    playerA_additonal_moves++;
}

void GameSnapshot::increment_playerB_additional_moves() {
    playerB_additonal_moves++;
}

int GameSnapshot::get_playerA_stones_captured() const {
    return playerA_stones_captured;
}

void GameSnapshot::set_playerA_stones_captured(int stones) {
    playerA_stones_captured = stones;
}

int GameSnapshot::get_playerB_stones_captured() const {
    return playerB_stones_captured;
}

void GameSnapshot::set_playerB_stones_captured(int stones) {
    playerB_stones_captured = stones;
}

vector<int> GameSnapshot::get_valid_moves() { 
    vector<int> valid_moves = current_turn->get_valid_moves(*this);
    random_device rd;
    mt19937 mt(rd());
    shuffle(valid_moves.begin(), valid_moves.end(), mt);
    cout << "**************************************************" << endl;
    for(int move : valid_moves) cout << move << " ";
    cout << "\n**************************************************" << endl;
    return valid_moves;
}

GameSnapshot::GameSnapshot(const GameSnapshot& other) 
: board(other.board),
current_turn(other.current_turn->clone()),
playerA_additonal_moves(other.playerA_additonal_moves),
playerB_additonal_moves(other.playerB_additonal_moves),
playerA_stones_captured(other.playerA_stones_captured),
playerB_stones_captured(other.playerB_stones_captured) {}

GameSnapshot& GameSnapshot::operator=(const GameSnapshot& other) {
    if (this != &other) {
        board = other.board;
        playerA_additonal_moves = other.playerA_additonal_moves;
        playerB_additonal_moves = other.playerB_additonal_moves;
        playerA_stones_captured = other.playerA_stones_captured;
        playerB_stones_captured = other.playerB_stones_captured;
        current_turn = other.current_turn->clone();
    }
    return *this;
}
