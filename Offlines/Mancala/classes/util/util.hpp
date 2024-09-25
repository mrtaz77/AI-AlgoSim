#pragma once
#include <string>
#include "../game/modes/Mode.hpp"
#include "../heuristics/Heuristic.hpp"
using namespace std;

int validate_move(string);
enum Modes validate_mode_choice(string);
enum Heuristics validate_heuristic_choice(string);