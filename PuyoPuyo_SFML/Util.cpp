#include "Util.h"
#include <stdlib.h>
#include <vector>
#include <iostream>

//return int between min (inclusive) and max(excusive)
int RandomInt(int min, int max)
{
	return rand() % (max - min) + min;
}

bool ContainPuyo(std::vector<Puyo*> vec, Puyo* key)
{
	if (std::find(vec.begin(), vec.end(), key) != vec.end()) {
		return true;
	}
	else {
		return false;
	}
}
