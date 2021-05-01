#include "GameManager.h"

int main()
{
	GameManager* _GameManager = GameManager::getInstance();
	_GameManager->loop();

	return 0;
}