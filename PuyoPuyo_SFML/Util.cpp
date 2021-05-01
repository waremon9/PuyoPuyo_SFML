#include "Util.h"
#include <stdlib.h>

//return int between min (inclusive) and max(excusive)
int RandomInt(int min, int max)
{
	return rand() % (max - min) + min;
}
