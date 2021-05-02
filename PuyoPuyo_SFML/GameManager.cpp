#include "GameManager.h"
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Puyo.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
	//project window
	window = new sf::RenderWindow(sf::VideoMode(1500, 900), "HelloWorld");
	window->setKeyRepeatEnabled(false);

	//clock for delta time
	DeltaClock = new sf::Clock();
	DeltaTime = 0;

	//set window update frequency
	Framerate = NextWindowUpdate = 1 / 144;

	//Game grid
	GameGrid = new Grid(GridSize, CellSize, GridPosition);
}

GameManager* GameManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new GameManager();
	}
	return Instance;
}

sf::RenderWindow* GameManager::getWindow() const
{
	return window;
}

void GameManager::loop()
{
	while (window->isOpen())
	{
		updateDeltaTime();

		manageEvent();

		updateWindow();
	}
}

void GameManager::updateDeltaTime()
{
	DeltaTime = DeltaClock->getElapsedTime().asSeconds();
	DeltaClock->restart();
}

void GameManager::manageEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			ActualPuyo = createPuyo();
	}
}

void GameManager::updateWindow()
{
	NextWindowUpdate -= DeltaTime;

	if (NextWindowUpdate <= 0) {
		NextWindowUpdate = Framerate;

		window->clear();

		GameGrid->Draw();
		for (Puyo* p : AllPuyo) {
			p->Draw();
		}

		window->display();
	}
}

Puyo* GameManager::createPuyo()
{
	Puyo* p = new Puyo(GameGrid->getDimension().x / 2, 0);

	AllPuyo.push_back(p);

	return p;
}

void GameManager::drawOnWindow(sf::Drawable* d)
{
	window->draw(*d);
}
