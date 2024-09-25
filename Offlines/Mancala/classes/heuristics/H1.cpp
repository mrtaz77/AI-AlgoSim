#include "H1.hpp"

int H1::evaluate(GameSnapshot* game_snap) {
    int eval = game_snap->get_storageA() - game_snap->get_storageB();
    if(game_snap->is_playerA_turn()) return eval;
    else return -eval;
}