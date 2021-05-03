#include "GameManager.h"
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Puyo.h"
#include <iostream>

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

	GameSpeed = 3.f;
	FallCooldown = FallCooldownBase = 1.f / GameSpeed;
	MainPuyo = nullptr;
	SecondPuyo = nullptr;
	_PuyoRotation = PuyoRotation::UP;
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

float GameManager::getGameSpeed() const
{
	return GameSpeed;
}

void GameManager::loop()
{
	while (window->isOpen())
	{
		updateDeltaTime();

		manageEvent();

		updateEntitys();

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

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			if (MainPuyo && SecondPuyo) MovePuyoRight();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			if (MainPuyo && SecondPuyo) MovePuyoLeft();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			if (MainPuyo && SecondPuyo) RotatePuyoLeft();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
			if (MainPuyo && SecondPuyo) RotatePuyoRight();
	}
}

void GameManager::updateEntitys()
{
	FallCooldown -= DeltaTime;
	if (FallCooldown <= 0) {
		FallCooldown = FallCooldownBase;

		if (MainPuyo && SecondPuyo) {
			if (MainPuyo->getCoordinate().y < GridSize.y - 1
			    && SecondPuyo->getCoordinate().y < GridSize.y - 1
				&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0, 1))  == nullptr
				&& GameGrid->getElementAt(SecondPuyo->getCoordinate() + sf::Vector2i(0, 1)) == nullptr)
			{
				MainPuyo->fall();
				SecondPuyo->fall();
			}
			else {
				GameGrid->addElementAt(MainPuyo->getCoordinate(), MainPuyo);
				GameGrid->addElementAt(SecondPuyo->getCoordinate(), SecondPuyo);
				createPuyo();
			}
			
		}
		else createPuyo();
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

void GameManager::createPuyo()
{
	Puyo* p1 = new Puyo(GameGrid->getDimension().x / 2 - 1, 1);
	MainPuyo = p1;
	AllPuyo.push_back(p1);

	Puyo* p2 = new Puyo(GameGrid->getDimension().x / 2 - 1, 0);
	SecondPuyo = p2;
	AllPuyo.push_back(p2);

	_PuyoRotation = PuyoRotation::UP;
	FallCooldown = FallCooldownBase;
}

void GameManager::MovePuyoRight()
{
	if (MainPuyo->getCoordinate().x < GridSize.x -1
		&& SecondPuyo->getCoordinate().x < GridSize.x - 1
		&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(1, 0)) == nullptr
		&& GameGrid->getElementAt(SecondPuyo->getCoordinate() + sf::Vector2i(1, 0)) == nullptr)
	{
		MainPuyo->moveRight();
		SecondPuyo->moveRight();
	}
}

void GameManager::MovePuyoLeft()
{
	if (MainPuyo->getCoordinate().x > 0
		&& SecondPuyo->getCoordinate().x > 0
		&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(-1, 0)) == nullptr
		&& GameGrid->getElementAt(SecondPuyo->getCoordinate() + sf::Vector2i(-1, 0)) == nullptr)
	{
		MainPuyo->moveLeft();
		SecondPuyo->moveLeft();
	}
}

void GameManager::RotatePuyoRight()
{
	switch (_PuyoRotation)
	{
	case PuyoRotation::UP:
		if (MainPuyo->getCoordinate().x < GridSize.x - 1
			&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(1,0)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(1,0));
			_PuyoRotation = PuyoRotation::RIGHT;
		}
		break;
	case PuyoRotation::RIGHT:
		if (GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0,1)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(0, 1));
			_PuyoRotation = PuyoRotation::DOWN;
		}
		break;
	case PuyoRotation::DOWN:
		if (MainPuyo->getCoordinate().x > 0
			&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(-1,0)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(-1, 0));
			_PuyoRotation = PuyoRotation::LEFT;
		}
		break;
	case PuyoRotation::LEFT:
		if (GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0,-1)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(0, -1));
			_PuyoRotation = PuyoRotation::UP;
		}
		break;
	default:
		break;
	}
}

void GameManager::RotatePuyoLeft()
{
	switch (_PuyoRotation)
	{
	case PuyoRotation::DOWN:
		if (MainPuyo->getCoordinate().x < GridSize.x - 1
			&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(1, 0)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(1, 0));
			_PuyoRotation = PuyoRotation::RIGHT;
		}
		break;
	case PuyoRotation::LEFT:
		if (GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0, 1)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(0, 1));
			_PuyoRotation = PuyoRotation::DOWN;
		}
		break;
	case PuyoRotation::UP:
		if (MainPuyo->getCoordinate().x > 0
			&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(-1, 0)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(-1, 0));
			_PuyoRotation = PuyoRotation::LEFT;
		}
		break;
	case PuyoRotation::RIGHT:
		if (GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0, -1)) == nullptr) {
			SecondPuyo->setCoordinate(MainPuyo->getCoordinate() + sf::Vector2i(0, -1));
			_PuyoRotation = PuyoRotation::UP;
		}
		break;
	default:
		break;
	}
}

void GameManager::drawOnWindow(sf::Drawable* d)
{
	window->draw(*d);
}
