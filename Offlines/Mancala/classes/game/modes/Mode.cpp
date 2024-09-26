#include "Mode.hpp"

Mode::Mode() {
    signal(SIGINT, keyboard_interrupt);
}

void Mode::keyboard_interrupt(int) {
    cout << "\nQuitting mancala..." << endl;
    exit(0); 
}