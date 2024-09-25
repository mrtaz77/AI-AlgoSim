#pragma once

#include <bits/stdc++.h>
#include "GameSnapshot.hpp"
#include "../util/util.hpp"

using namespace std;

class GameIO {
    unique_ptr<GameSnapshot> game_snap;
public:
    void start();
    void prompt_player_turn();
    int get_player_move();
    void declare_winner();
    static void keyboard_interrupt(int);
};