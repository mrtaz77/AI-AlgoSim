#pragma once

#include <bits/stdc++.h>
#include "Mode.hpp"
#include "HumanVsHuman.hpp"
#include "HumanVsAI.hpp"
#include "AIVsAI.hpp"
#include "Modes.hpp"

using namespace std;

class ModeFactory {
public:
    static unique_ptr<Mode> createGameMode(Modes);
};