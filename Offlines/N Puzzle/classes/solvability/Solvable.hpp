#pragma once
#include <vector>
using namespace std;

class Solvable {
	public:
	virtual bool is_solvable(int, int) = 0;
};