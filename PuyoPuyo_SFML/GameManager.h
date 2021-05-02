#pragma once
#include "SFML/Graphics.hpp"

class Grid;
class Puyo;

class GameManager
{
private:
	static GameManager* Instance;

	sf::RenderWindow* window;
	sf::Clock* DeltaClock;
	float DeltaTime;
	float Framerate;
	float NextWindowUpdate;
	float GameSpeed;

	Grid* GameGrid;
	std::vector<Puyo*> AllPuyo;

	Puyo* CurrentPuyo;
	float FallCooldown;
	float FallCooldownBase;

public:
	const int CellSize = 64;
	const sf::Vector2i GridSize = sf::Vector2i(6, 10);
	const int PuyoSpriteSize = 32;
	const sf::Vector2f GridPosition = sf::Vector2f(100, 100);

public:
	GameManager();

	void loop();
	void updateDeltaTime();
	void manageEvent();
	void updateEntitys();
	void updateWindow();

	Puyo* createPuyo();

	void drawOnWindow(sf::Drawable*);

	static GameManager* getInstance();
	sf::RenderWindow* getWindow() const;
	float getGameSpeed() const;
};

