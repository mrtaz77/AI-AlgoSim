#pragma once

#include <bits/stdc++.h>
#include "Mode.hpp"
#include "HumanVsHuman.hpp"
#include "HumanVsAI.hpp"

using namespace std;

class ModeFactory {
public:
    static unique_ptr<Mode> createGameMode(enum Modes);
};