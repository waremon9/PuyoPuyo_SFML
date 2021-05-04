#include "GameManager.h"

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	GameManager* _GameManager = GameManager::getInstance();
	_GameManager->loop();

	return 0;
}