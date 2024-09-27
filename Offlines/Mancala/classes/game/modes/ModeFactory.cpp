#include "ModeFactory.hpp"

unique_ptr<Mode> ModeFactory::createGameMode(Modes mode) {
    switch (mode) {
        case Modes::HUMAN_VS_HUMAN:
            return make_unique<HumanVsHuman>();
        case Modes::HUMAN_VS_AI:
            return make_unique<HumanVsAI>();
        case Modes::AI_VS_HUMAN:
            return make_unique<AIVsHuman>();
        case Modes::AI_VS_AI:
            return make_unique<AIVsAI>();
        default:
            return nullptr;
    }
}