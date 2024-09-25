#include "HumanVsHuman.hpp"

void HumanVsHuman::prompt_player_turn(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) cout << "Player A's turn: ";
    else cout << "Player B's turn: ";
}

int HumanVsHuman::get_player_move() {
    string in;
    cin >> in;
    return validate_move(in);
}