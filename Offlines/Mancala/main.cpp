#include <iostream>
#include "./classes/game/GameIO.hpp"

using namespace std;

int main() {
    GameIO game;
    game.chose_mode();
    game.start();
}