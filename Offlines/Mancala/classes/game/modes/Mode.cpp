#include "Mode.hpp"

Mode::Mode() {
    signal(SIGINT, keyboard_interrupt);
}

void Mode::keyboard_interrupt(int) {
    cout << "\nQuitting mancala..." << endl;
    exit(0); 
}

Heuristic* Mode::prompt_heuristics() {
    cout << "Available Heuristics : H1(1), H2(2), H3(3), H4(4)" << endl;
    cout << "Enter heuristic: ";
    string in;
    cin >> in;
    Heuristics h = validate_heuristic_choice(in);
    if(h == Heuristics::INVALID) {
        cout << "Invalid heuristic" << endl;
        exit(1);
    }
    return HeuristicFactory::create_heuristic((Heuristics)h);
}

int Mode::prompt_depth() {
    int depth;
    cout << "Enter depth: ";
    cin >> depth;
    return depth;
}