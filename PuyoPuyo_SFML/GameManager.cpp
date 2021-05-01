#include "GameManager.h"
#include "SFML/Graphics.hpp"

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
}

GameManager* GameManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new GameManager();
	}
	return Instance;
}

void GameManager::loop()
{
	while (window->isOpen())
	{
		updateDeltaTime();

		manageEvent();
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
	}
}

void GameManager::updateWindow()
{
	NextWindowUpdate -= DeltaTime;

	if (NextWindowUpdate <= 0) {
		NextWindowUpdate = Framerate;

		window->clear();

		window->display();
	}
}

void GameManager::drawOnWindow(sf::Drawable* d)
{
	window->draw(*d);
}
