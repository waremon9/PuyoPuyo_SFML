#include "HUDManager.h"
#include "SFML/Graphics.hpp"
#include "RessourcesManager.h"
#include "GameManager.h"
#include <iostream>

HUDManager* HUDManager::Instance = nullptr;

HUDManager::HUDManager()
{
	RessourcesManager* RM = RessourcesManager::getInstance();

	ScorePlayer1 = new sf::Text();
	ScorePlayer1->setFont(*RM->getFont(RessourcesManager::MLFont));
	ScorePlayer1->setPosition(sf::Vector2f(500,600));
	updateScore();
}

HUDManager* HUDManager::getInstance()
{

	if (Instance == nullptr) {
		Instance = new HUDManager();
	}
	return Instance;
}

void HUDManager::updateScore()
{
	GameManager* GM = GameManager::getInstance();

	ScorePlayer1->setString("Score : " + std::to_string(GM->getScoreplayer1()));
}

void HUDManager::Draw()
{
	GameManager* GM = GameManager::getInstance();

	GM->drawOnWindow(ScorePlayer1);
}
