#include "./classes/game/GameIO.hpp"

int main() {
    GameIO game;
    game.chose_mode();
    game.set_number_of_matches();
    game.start();
    game.display_final_results();
}