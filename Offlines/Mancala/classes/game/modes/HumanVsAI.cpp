#include "HumanVsAI.hpp"

HumanVsAI::HumanVsAI() : ai(AI(prompt_heuristics(), prompt_depth())) {}

void HumanVsAI::prompt_player_turn(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) cout << "Player A's turn: ";
    else cout << "AI's turn..." << endl;
}

int HumanVsAI::get_player_move(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) {
        string in;
        cin >> in;
        return validate_move(in);
    }
    else {
        int move = ai.decide_move(make_unique<GameSnapshot>(*game_snap));
        cout << "AI chose move: " << move << endl;
        return move;
    }
}