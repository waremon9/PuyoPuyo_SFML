#pragma once
#include "SFML/Graphics.hpp"

class Grid;

class GameManager
{
private:
	static GameManager* Instance;

	sf::RenderWindow* window;
	sf::Clock* DeltaClock;
	float DeltaTime;
	float Framerate;
	float NextWindowUpdate;

	Grid* GameGrid;

public:
	GameManager();

	void loop();
	void updateDeltaTime();
	void manageEvent();
	void updateWindow();

	void drawOnWindow(sf::Drawable*);

	static GameManager* getInstance();
	sf::RenderWindow* getWindow() const;
};

