#include "ModeFactory.hpp"

unique_ptr<Mode> ModeFactory::createGameMode(enum Modes mode) {
    switch (mode) {
        case Modes::PLAYER_VS_AI:
            return make_unique<HumanVsHuman>();
        default:
            return nullptr;
    }
}