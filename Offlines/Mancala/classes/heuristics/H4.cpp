#include "H4.hpp"

H4::H4(int W1, int W2, int W3, int W4) : W1(W1), W2(W2), W3(W3), W4(W4) {}

int H4::evaluate(GameSnapshot* game_snap) {
    int eval = W1 * (game_snap->get_storageA() - game_snap->get_storageB())
    + W2 * (game_snap->get_stones_in_mancalaA() - game_snap->get_stones_in_mancalaB());
    if(game_snap->is_playerA_turn()) 
        return eval + W3 * game_snap->get_playerA_additional_moves() + W4 * game_snap->get_playerA_stones_captured();
    else 
        return -eval + W3 * game_snap->get_playerB_additional_moves() + W4 * game_snap->get_playerB_stones_captured();
}