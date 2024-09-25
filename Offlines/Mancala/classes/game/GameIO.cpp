#include "GameIO.hpp"

void GameIO::start() {
    signal(SIGINT, GameIO::keyboard_interrupt);

    game_snap = make_unique<GameSnapshot>();
    cout << "*** Welcome to Mancala ***" << endl;
    cout << *game_snap;

    while (!game_snap->is_game_over()) {
        prompt_player_turn();
        int move = get_player_move();
        if(move == -1) continue;
        game_snap->make_move(move);
        cout << *game_snap;
    }
    declare_winner();
}

void GameIO::keyboard_interrupt(int) {
    cout << "\nQuitting mancala..." << endl;
    exit(0); 
}

int GameIO::get_player_move() {
    string in;
    cin >> in;
    return validate_move(in);
}

void GameIO::prompt_player_turn() {
    if (game_snap->is_playerA_turn()) cout << "Player A's turn: ";
    else cout << "Player B's turn: ";
}

void GameIO::declare_winner() {
    int playerA_points = game_snap->get_storageA();
    int playerB_points = game_snap->get_storageB();
    cout << "\n+-----------------+-----------------+\n";
    cout << "|    Player       |     Points      |\n";
    cout << "+-----------------+-----------------+\n";
    cout << "|    Player A     |      " << setw(5) << playerA_points << "      |\n";
    cout << "+-----------------+-----------------+\n";
    cout << "|    Player B     |      " << setw(5) << playerB_points << "      |\n";
    cout << "+-----------------+-----------------+\n";
    cout << "\nFinal Result: ";
    if (playerA_points > playerB_points) {
        cout << "Player A wins!\n";
    } else if (playerB_points > playerA_points) {
        cout << "Player B wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
}
