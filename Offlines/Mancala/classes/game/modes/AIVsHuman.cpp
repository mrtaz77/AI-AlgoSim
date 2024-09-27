#include "AIVsHuman.hpp"

AIVsHuman::AIVsHuman() : ai(AI(prompt_heuristics(), prompt_depth())) {}

void AIVsHuman::prompt_player_turn(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) cout << "AI's turn..." << endl;
    else cout << "Player B's turn: ";
}

int AIVsHuman::get_player_move(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) {
        int move = ai.decide_move(make_unique<GameSnapshot>(*game_snap));
        cout << "AI chose move: " << move << endl;
        return move;
        }
    else {
        string in;
        cin >> in;
        return validate_move(in);
    }
}