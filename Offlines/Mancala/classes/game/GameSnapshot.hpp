#pragma once

#include <bits/stdc++.h>
#include "../turn/Turn.hpp"
#include "../turn/PlayerATurn.hpp"
#include "../util/util.hpp"
using namespace std;

class GameSnapshot {
    vector<int> board;
    unique_ptr<Turn> current_turn;
    int playerA_additonal_moves;
    int playerB_additonal_moves;
    int playerA_stones_captured;
    int playerB_stones_captured;
public:
    GameSnapshot();
    GameSnapshot(const GameSnapshot&);
    GameSnapshot& operator=(const GameSnapshot&);
    friend ostream& operator<<(ostream&, const GameSnapshot&);
    void make_move(int, bool);
    bool is_playerA_turn() const;
    bool is_game_over();
    int get_stones_in_bin(int);
    void set_stones_in_bin(int, int);
    int get_storageA() const;
    int get_storageB() const;
    int get_stones_in_mancalaA() const;
    int get_stones_in_mancalaB() const;
    void finish_game(int, int);
    int get_playerA_additional_moves() const;
    void increment_playerA_additional_moves();
    int get_playerB_additional_moves() const;
    void increment_playerB_additional_moves();
    int get_playerA_stones_captured() const;
    void set_playerA_stones_captured(int);
    int get_playerB_stones_captured() const;
    void set_playerB_stones_captured(int);
    vector<int> get_valid_moves();
    void change_turn();
};