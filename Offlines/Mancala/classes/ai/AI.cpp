#include "AI.hpp"

AI::AI(Heuristic* heuristic, int depth) : heuristic(heuristic), depth(depth) {}

int AI::decide_move(unique_ptr<GameSnapshot> game_snap) {
    int bestMove = -1;
    int bestScore = numeric_limits<int>::min();
    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();
    playerTurn = game_snap->is_playerA_turn();

    vector<int> valid_moves = game_snap->get_valid_moves();

    for(int valid_move : valid_moves) {
        unique_ptr<GameSnapshot> new_game_snap = make_unique<GameSnapshot>(*game_snap);
        bool currentTurn = new_game_snap->is_playerA_turn();
        new_game_snap->make_move(valid_move);
        int score = minimax(move(new_game_snap), depth - 1, alpha, beta, currentTurn == new_game_snap->is_playerA_turn());
        // cout << "Depth: " << depth << " Alpha: max(" << bestScore << ", " << score << ", " << alpha << ") = "; 
        if(score > bestScore) {
            bestMove = valid_move;
        }
        bestScore = max(bestScore, score);
        alpha = max(alpha, score);
        // cout << alpha << endl;
        if(beta <= alpha) break;
    }
    return bestMove;
}

int AI::minimax(unique_ptr<GameSnapshot> game_snap, int depth, int alpha, int beta, bool maximizing_player) {
    // cout << "\n===================================" << endl;
    // cout << *game_snap;
    // cout << "AI Player turn: " << boolalpha << !game_snap->is_playerA_turn() << endl;
    // cout << "===================================" << endl;
    if(game_snap->is_game_over() || depth == 0 ) {
        // cout << *game_snap << endl;
        if(playerTurn != game_snap->is_playerA_turn()) game_snap->change_turn();
        int eval = heuristic->evaluate(game_snap.get()) ;
        // cout << "Depth: " << depth << " Heuristic: " << eval << endl;
        return eval;
    }
    if(maximizing_player) {
        int maxEval = numeric_limits<int>::min();
        vector<int> valid_moves = game_snap->get_valid_moves();
        for(int valid_move : valid_moves) {
            unique_ptr<GameSnapshot> new_game_snap = make_unique<GameSnapshot>(*game_snap);
            bool currentTurn = new_game_snap->is_playerA_turn();
            new_game_snap->make_move(valid_move);
            int eval = minimax(move(new_game_snap), depth - 1, alpha, beta, currentTurn == new_game_snap->is_playerA_turn());
            // cout << "Depth: " << depth << " Alpha: max(" << maxEval << ", " << eval << ", " << alpha << ") = "; 
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            // cout << alpha << endl;
            if(beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        vector<int> valid_moves = game_snap->get_valid_moves();
        for(int valid_move : valid_moves) {
            unique_ptr<GameSnapshot> new_game_snap = make_unique<GameSnapshot>(*game_snap);
            bool currentTurn = new_game_snap->is_playerA_turn();
            new_game_snap->make_move(valid_move);
            int eval = minimax(move(new_game_snap), depth - 1, alpha, beta, !(currentTurn == new_game_snap->is_playerA_turn()));
            // cout << "Depth: " << depth << " Beta: min(" << minEval << ", " << eval << ", " << beta << ") = "; 
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            // cout << beta << endl;
            if(beta <= alpha) break;
        }
        return minEval;
    }
}