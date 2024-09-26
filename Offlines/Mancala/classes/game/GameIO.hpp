#pragma once

#include <bits/stdc++.h>
#include "GameSnapshot.hpp"
#include "../util/util.hpp"
#include "./modes/Mode.hpp"
#include "./modes/ModeFactory.hpp"

using namespace std;

class GameIO {
    unique_ptr<GameSnapshot> game_snap;
    unique_ptr<Mode> mode;
    int number_of_matches;
    int playerAWins;
    int playerBWins;
    int draws;
public:
    GameIO();
    void chose_mode();
    void start();
    void match();
    void declare_winner();
    static void keyboard_interrupt(int);
    void set_number_of_matches();
    void update_results();
    void display_final_results();
};