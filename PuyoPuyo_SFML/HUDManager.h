#pragma once
#include "SFML/Graphics.hpp"

class HUDManager
{
private:
	static HUDManager* Instance;

	sf::Text* ScorePlayer1;

public:
	HUDManager();
	static HUDManager* getInstance();

	void updateScore();
	void Draw();
};

