#include "H2.hpp"

H2::H2(int W1, int W2) : W1(W1), W2(W2) {}

int H2::evaluate(GameSnapshot* game_snap) {
    int eval = W1 * (game_snap->get_storageA() - game_snap->get_storageB())
    + W2 * (game_snap->get_stones_in_mancalaA() - game_snap->get_stones_in_mancalaB());
    if(game_snap->is_playerA_turn()) return eval;
    else return -eval;
}