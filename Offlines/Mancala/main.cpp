#include <iostream>
#include "./classes/game/GameIO.hpp"

using namespace std;

int main() {
    GameIO game;
    game.chose_mode();
    game.set_number_of_matches();
    game.start();
    game.display_final_results();
}