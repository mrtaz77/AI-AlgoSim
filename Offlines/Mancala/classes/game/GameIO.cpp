#include "GameIO.hpp"

GameIO::GameIO() : 
game_snap(make_unique<GameSnapshot>()),
number_of_games(0),
playerAWins(0),
playerBWins(0),
draws(0) {
    cout << "***** Welcome to Mancala *****" << endl;
    signal(SIGINT, keyboard_interrupt);
}

void GameIO::start() {
    for (int i = 0; i < number_of_games; i++) {
        cout << "\n*** Match " << (i+1) << " ***" << endl;
        match();
        update_results();
        game_snap = make_unique<GameSnapshot>();
    }
}

void GameIO::match() {
    cout << *game_snap;
    while (!game_snap->is_game_over()) {
        mode->prompt_player_turn(game_snap.get());
        int move = mode->get_player_move();
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

void GameIO::declare_winner() {
    int playerA_points = game_snap->get_storageA();
    int playerB_points = game_snap->get_storageB();
    cout << endl;
    cout << "+-----------+------------+\n";
    cout << "|  Players  |   Points   |\n";
    cout << "+-----------+------------+\n";
    cout << "|     A     |   " << setw(6) << playerA_points << "   |\n";
    cout << "+-----------+------------+\n";
    cout << "|     B     |   " << setw(6) << playerB_points << "   |\n";
    cout << "+-----------+------------+\n";
    cout << "\nFinal Result: ";
    if (playerA_points > playerB_points) {
        cout << "Player A wins!\n";
    } else if (playerB_points > playerA_points) {
        cout << "Player B wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
}

void GameIO::chose_mode() {
    string choice;
    cout << "Select Game Mode:\n";
    cout << "1) Human vs Human\n";
    cout << "2) Human vs AI (Coming Soon)\n";
    cout << "3) AI vs AI (Coming Soon)\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Modes mode_choice = validate_choice(choice);
    if (mode_choice == Modes::INVALID) {
        cout << "Invalid choice. Exiting mancala...\n";
        exit(0);
    }
    mode = ModeFactory::createGameMode(mode_choice);
}

void GameIO::set_number_of_games() {
    string n;
    cout << "Enter number of games to play: ";
    cin >> n;
    number_of_games = validate_move(n);
    if (number_of_games < 1) {
        cout << "Invalid number of games. Exiting mancala...\n";
        exit(0);
    }
}

void GameIO::update_results() {
    if (game_snap->get_storageA() > game_snap->get_storageB()) {
        playerAWins++;
    } else if (game_snap->get_storageB() > game_snap->get_storageA()) {
        playerBWins++;
    } else {
        draws++;
    }
}

void GameIO::display_final_results() {
    cout << "\n+-----------------+------------+\n";
    cout << "|     Results     |   Games    |\n";
    cout << "+-----------------+------------+\n";
    cout << "| Player A Wins   |   " << setw(6) << playerAWins << "   |\n";
    cout << "+-----------------+------------+\n";
    cout << "| Player B Wins   |   " << setw(6) << playerBWins << "   |\n";
    cout << "+-----------------+------------+\n";
    cout << "| Draws           |   " << setw(6) << draws << "   |\n";
    cout << "+-----------------+------------+\n";
    
    if (number_of_games > 0) {
        cout << "| Player A Win%   |   " << setw(5) << fixed << setprecision(2) << (playerAWins * 100.0) / number_of_games << "%   |\n";
        cout << "+-----------------+------------+\n";
        cout << "| Player B Win%   |   " << setw(5) << fixed << setprecision(2) << (playerBWins * 100.0) / number_of_games << "%   |\n";
    } else {
        cout << "| Player A Win%   |     N/A    |\n";
        cout << "+-----------------+------------+\n";
        cout << "| Player B Win%   |     N/A    |\n";
    }

    cout << "+-----------------+------------+\n";
    cout << "\n";
}