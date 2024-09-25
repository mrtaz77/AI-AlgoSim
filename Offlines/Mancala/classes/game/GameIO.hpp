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
public:
    GameIO();
    void chose_mode();
    void start();
    void declare_winner();
    static void keyboard_interrupt(int);
};