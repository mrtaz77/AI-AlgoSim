#include "PlayerATurn.hpp"

bool PlayerATurn::is_valid_turn(GameSnapshot& game_snap, int bin_index) {
    if(bin_index >=0
    && bin_index < NUM_OF_BINS_PER_SIDE
    && game_snap.get_stones_in_bin(bin_index) > 0) return true;
    else {
        cout << "Invalid move; valid moves: ";
        for(int i = 0; i < NUM_OF_BINS_PER_SIDE; i++) {
            if(game_snap.get_stones_in_bin(i) > 0) cout << i << " ";
        }
        cout << endl;
        return false;
    }
}

void PlayerATurn::make_move(GameSnapshot& game_snap, int bin_index) {
    int stones = game_snap.get_stones_in_bin(bin_index);
    game_snap.set_stones_in_bin(bin_index, 0);
    int i = bin_index + 1;
    while (stones > 0) {
        i = (i + 1) % BOARD_SIZE;
        game_snap.set_stones_in_bin(i, game_snap.get_stones_in_bin(i) + 1);
        stones--;
    }
    if (i == NUM_OF_BINS_PER_SIDE + 1) {
        game_snap.increment_playerA_additional_moves();
        return; // last stone in own storage
    }
    if (
        i <= NUM_OF_BINS_PER_SIDE // own mancala
        && game_snap.get_stones_in_bin(i - 1) == 1 // last stone in empty bin 
        && game_snap.get_stones_in_bin(BOARD_SIZE - i - 1) > 0 // opposite bin not empty
    ) {
        game_snap.set_playerA_stones_captured(game_snap.get_playerA_stones_captured() + game_snap.get_stones_in_bin(BOARD_SIZE - i - 1));
        game_snap.set_stones_in_bin(NUM_OF_BINS_PER_SIDE, game_snap.get_storageA() + game_snap.get_stones_in_bin(BOARD_SIZE - i - 1) + 1);
        game_snap.set_stones_in_bin(BOARD_SIZE - i - 1, 0);
        game_snap.set_stones_in_bin(i - 1, 0);
    }
    game_snap.change_turn();
}

vector<int> PlayerATurn::get_valid_moves(GameSnapshot& game_snap) {
    vector<int> valid_moves;
    for(int i = 0; i < NUM_OF_BINS_PER_SIDE; i++) {
        if(game_snap.get_stones_in_bin(i) > 0) valid_moves.push_back(i);
    }
    return valid_moves;
}

unique_ptr<Turn> PlayerATurn::clone() { return make_unique<PlayerATurn>(*this); }