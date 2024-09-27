#include "AIVsAI.hpp"

AIVsAI::AIVsAI() {
    cout << "** AI Player A **" << endl;
    playerA = AI(prompt_heuristics(), prompt_depth());
    cout << "** AI Player B **" << endl;
    playerB = AI(prompt_heuristics(), prompt_depth());
}

void AIVsAI::prompt_player_turn(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) cout << "AI Player A's turn..." << endl;
    else cout << "AI Player B's turn..." << endl;
}

int AIVsAI::get_player_move(GameSnapshot *game_snap) {
    if (game_snap->is_playerA_turn()) {
        int move = playerA.decide_move(make_unique<GameSnapshot>(*game_snap));
        cout << "AI Player A chose move: " << move << endl;
        return move;
    }
    else {
        int move = playerB.decide_move(make_unique<GameSnapshot>(*game_snap));
        cout << "AI Player B chose move: " << move << endl;
        return move;
    }
}