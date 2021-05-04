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
	Gravity = false;
	GravityCooldown = GravityCooldownBase = FallCooldownBase / 2.f;
	ChainBonus = 0;
	Score = 0;
	FastFall = false;
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

		DeleteEntity();

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

		if (!Gravity) {
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
}

void GameManager::updateEntitys()
{
	if (!Gravity) {

		FallCooldown -= DeltaTime;
		if (FallCooldown <= 0) {
			FallCooldown = FallCooldownBase;

			if (MainPuyo && SecondPuyo) {
				if (MainPuyo->getCoordinate().y < GridSize.y - 1
					&& SecondPuyo->getCoordinate().y < GridSize.y - 1
					&& GameGrid->getElementAt(MainPuyo->getCoordinate() + sf::Vector2i(0, 1)) == nullptr
					&& GameGrid->getElementAt(SecondPuyo->getCoordinate() + sf::Vector2i(0, 1)) == nullptr)
				{
					MainPuyo->fall();
					SecondPuyo->fall();
				}
				else {
					GameGrid->addElementAt(MainPuyo->getCoordinate(), MainPuyo);
					GameGrid->addElementAt(SecondPuyo->getCoordinate(), SecondPuyo);

					for (Puyo* adj : GameGrid->getAdjacentPuyo(MainPuyo)) {
						if (adj) GameGrid->DeterminePuyoState(adj);
					}
					for (Puyo* adj : GameGrid->getAdjacentPuyo(SecondPuyo)) {
						if (adj) GameGrid->DeterminePuyoState(adj);
					}

					Gravity = true;
				}

			}
			else createPuyo();
		}
	}
	else
	{
		GravityCooldown -= DeltaTime;
		if (GravityCooldown <= 0) {
			GravityCooldown = GravityCooldownBase;

			if (GameGrid->MakePuyoFall()) {
				ActualGroup = GameGrid->CheckForGroup();
				if (ActualGroup.size()==0) {
					Gravity = false;
					ChainBonus = 0;
					createPuyo();
				}
				else
				{
					ChainBonus++;
					calculateGroupScore();
				}
			}
		}
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

void GameManager::DeleteEntity()
{
	for (int i = AllPuyo.size() - 1; i >= 0; i--) {
		if (AllPuyo[i]->getDelete()) {
			GameGrid->removeElementAt(AllPuyo[i]->getCoordinate());
			delete AllPuyo[i];
			AllPuyo.erase(AllPuyo.begin() + i);
		}
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

void GameManager::calculateGroupScore()
{
	int groupScore = 0;

	int ChaB = 0;
	if (ChainBonus == 2) {
		ChaB = 8;
	}
	else if(ChainBonus == 3) {
		ChaB = 16;
	}
	else if (ChainBonus > 3) {
		ChaB = 32;
		while (ChainBonus > 4) {
			ChaB += 32;
			ChainBonus--;
		}
	}

	std::vector<PuyoColor> colors;
	bool alreadyIn = false;
	int ColDiff = 0;

	for (std::vector<Puyo*> chain : ActualGroup) {
		alreadyIn = false;
		for (PuyoColor p : colors) {
			if (chain[0]->getColor() == p) {
				alreadyIn = true;
			}
		}
		if (!alreadyIn) ColDiff++;
	}

	int ColB = 0;
	while (ColDiff>1)
	{
		ColB += 3;
	}

	for (std::vector<Puyo*> chain : ActualGroup) {
		int GB = 0;
		int taille = chain.size();
		if (taille > 4 && taille < 11) GB = taille - 3;
		else if (taille >= 11) GB = 10;

		int allBonus = ChaB + ColB + GB;
		if (allBonus <= 0) allBonus = 1;

		std::cout << allBonus << "\n";

		groupScore += (chain.size() * 10) * (allBonus);
	}

	addScore(groupScore);
}

void GameManager::addScore(int s)
{
	Score += s;

	std::cout << Score << "\n";
}

void GameManager::drawOnWindow(sf::Drawable* d)
{
	window->draw(*d);
}
