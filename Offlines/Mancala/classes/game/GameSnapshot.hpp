#pragma once

#include <bits/stdc++.h>
#include "../turn/Turn.hpp"
#include "../constants/Constants.hpp"
using namespace std;

class GameSnapshot {
    vector<int> board;
    bool is_turn_of_A;
    unique_ptr<Turn> currentTurn;
public:
    GameSnapshot();
    friend ostream& operator<<(ostream&, const GameSnapshot&);
    void makeMove(int);
    void setTurn();
    bool isPlayerATurn() const;
    bool isGameOver() const;
    int getBin(int);
    int getStorageA() const;
    int getStorageB() const;
};