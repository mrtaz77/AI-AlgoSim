#pragma once

#include <bits/stdc++.h>
#include "../turn/Turn.hpp"
#include "../turn/PlayerATurn.hpp"
#include "../constants/Constants.hpp"
using namespace std;

class GameSnapshot {
    vector<int> board;
    unique_ptr<Turn> current_turn;
public:
    GameSnapshot();
    friend ostream& operator<<(ostream&, const GameSnapshot&);
    void make_move(int);
    bool is_playerA_turn() const;
    void set_turn(unique_ptr<Turn>);
    bool is_game_over() const;
    int get_stones_in_bin(int);
    void set_stones_in_bin(int, int);
    int get_storageA() const;
    int get_storageB() const;
};