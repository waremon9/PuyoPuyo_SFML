#pragma once
#include "SFML/Graphics.hpp"

class GameManager
{
private:
	static GameManager* Instance;

	sf::RenderWindow* window;
	sf::Clock* DeltaClock;
	float DeltaTime;
	float Framerate;
	float NextWindowUpdate;

public:
	GameManager();

	void loop();
	void updateDeltaTime();
	void manageEvent();
	void updateWindow();

	void drawOnWindow(sf::Drawable*);

	static GameManager* getInstance();
};

