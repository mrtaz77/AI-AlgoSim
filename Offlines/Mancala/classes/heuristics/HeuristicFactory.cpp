#include "HeuristicFactory.hpp"

Heuristic* HeuristicFactory::create_heuristic(Heuristics h) {
    switch(h) {
        case H1:
            return new class H1();
        case H2: {
            int W1, W2;
            cout << "Enter two parameters for H2: ";
            cin >> W1 >> W2;
            return new class H2(W1, W2);
        }
        case H3: {
            int W1, W2, W3;
            cout << "Enter three parameters for H3: ";
            cin >> W1 >> W2 >> W3;
            return new class H3(W1, W2, W3);
        }
        case H4: {
            int W1, W2, W3, W4;
            cout << "Enter four parameters for H4: ";
            cin >> W1 >> W2 >> W3 >> W4;
            return new class H4(W1, W2, W3, W4);
        }
        default:
            return nullptr;
    }
}