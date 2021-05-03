#pragma once
#include "SFML/Graphics.hpp"

class Grid;
class Puyo;

enum class PuyoRotation {
	UP,
	LEFT,
	DOWN,
	RIGHT
};

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

	Puyo* MainPuyo;
	Puyo* SecondPuyo;
	PuyoRotation _PuyoRotation;

	float FallCooldown;
	float FallCooldownBase;

public:
	const int CellSize = 64;
	const sf::Vector2i GridSize = sf::Vector2i(6, 13);
	const int PuyoSpriteSize = 32;
	const sf::Vector2f GridPosition = sf::Vector2f(100, 50);

public:
	GameManager();

	void loop();
	void updateDeltaTime();
	void manageEvent();
	void updateEntitys();
	void updateWindow();

	void createPuyo();
	void MovePuyoRight();
	void MovePuyoLeft();
	void RotatePuyoRight();
	void RotatePuyoLeft();

	void drawOnWindow(sf::Drawable*);

	static GameManager* getInstance();
	sf::RenderWindow* getWindow() const;
	float getGameSpeed() const;
};

