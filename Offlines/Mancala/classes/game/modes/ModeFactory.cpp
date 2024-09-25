#include "ModeFactory.hpp"

unique_ptr<Mode> ModeFactory::createGameMode(enum Modes mode) {
    switch (mode) {
        case Modes::HUMAN_VS_HUMAN:
            return make_unique<HumanVsHuman>();
        case Modes::HUMAN_VS_AI:
            return nullptr;
        case Modes::AI_VS_AI:
            return nullptr;
        default:
            return nullptr;
    }
}