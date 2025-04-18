#include "PlayerBTurn.hpp"

bool PlayerBTurn::is_valid_turn(GameSnapshot& game_snap, int bin_index) {
    if(bin_index > NUM_OF_BINS_PER_SIDE
    && bin_index < BOARD_SIZE - 1
    && game_snap.get_stones_in_bin(bin_index) > 0) return true;
    else {
        cout << "Invalid move; valid moves: ";
        for(int i = NUM_OF_BINS_PER_SIDE + 1; i < BOARD_SIZE - 1; i++) {
            if(game_snap.get_stones_in_bin(i) > 0) cout << i << " ";
        }
        cout << endl;
        return false;
    }
}

void PlayerBTurn::make_move(GameSnapshot& game_snap, int bin_index) {
    int stones = game_snap.get_stones_in_bin(bin_index);
    game_snap.set_stones_in_bin(bin_index, 0);
    int i = bin_index + 1;
    while (stones > 0) {
        if(i == NUM_OF_BINS_PER_SIDE) {
            i++;
            continue; // skip player A's mancala
        } 
        game_snap.set_stones_in_bin(i, game_snap.get_stones_in_bin(i) + 1);
        stones--;
        if (i == BOARD_SIZE - 1) i = 0;
        else i++;
    }
    if (!i) {
        game_snap.increment_playerB_additional_moves();
        return; 
        // last stone in own storage
    }
    if (
        i < BOARD_SIZE
        && i > NUM_OF_BINS_PER_SIDE + 1 // own mancala
        && game_snap.get_stones_in_bin(i - 1) == 1 // last stone in empty bin 
        && game_snap.get_stones_in_bin(BOARD_SIZE - i - 1) > 0 // opposite bin not empty
    ) {
        game_snap.set_playerB_stones_captured(game_snap.get_playerB_stones_captured() + game_snap.get_stones_in_bin(BOARD_SIZE - i - 1) + 1);
        game_snap.set_stones_in_bin(BOARD_SIZE - 1, game_snap.get_storageB() + game_snap.get_stones_in_bin(BOARD_SIZE - i - 1) + 1);
        game_snap.set_stones_in_bin(BOARD_SIZE - i - 1, 0);
        game_snap.set_stones_in_bin(i - 1, 0);
    }
    game_snap.change_turn();
}

vector<int> PlayerBTurn::get_valid_moves(GameSnapshot& game_snap) {
    vector<int> valid_moves;
    for(int i = NUM_OF_BINS_PER_SIDE + 1; i < BOARD_SIZE - 1; i++) {
        if(game_snap.get_stones_in_bin(i) > 0) valid_moves.push_back(i);
    }
    return valid_moves;
}

unique_ptr<Turn> PlayerBTurn::clone() { return make_unique<PlayerBTurn>(*this); }