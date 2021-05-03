#include "Puyo.h"
#include "Util.h"
#include "GameManager.h"
#include "RessourcesManager.h"
#include <iostream>

Puyo::Puyo()
{
	GridCoordinate = sf::Vector2i(0, 0);
	State = PuyoState::Neutral;
	Color = PuyoColor::Red;
	setSpriteInfo();
}

Puyo::Puyo(int x, int y)
{
	GridCoordinate = sf::Vector2i(x, y);
	State = PuyoState::Neutral;
	Color = randomColor();
	setSpriteInfo();
}

Puyo::Puyo(sf::Vector2i coord)
{
	GridCoordinate = coord;
	State = PuyoState::Neutral;
	Color = randomColor();
	setSpriteInfo();
}

void Puyo::setSpriteInfo()
{
	RessourcesManager* RM = RessourcesManager::getInstance();

	_Sprite = new sf::Sprite();
	_Sprite->setTexture(*RM->getTexture(RessourcesManager::PuyoSpriteSheet));
	updateSpriteRect();
	_Sprite->setScale(2,2);

	updatePosition();
}

void Puyo::updatePosition()
{
	GameManager* GM = GameManager::getInstance();
	_Sprite->setPosition((sf::Vector2f)(GridCoordinate * GM->CellSize) + GM->GridPosition);
}

void Puyo::updateSpriteRect()
{
	GameManager* GM = GameManager::getInstance();
	_Sprite->setTextureRect(sf::IntRect((int)State * GM->PuyoSpriteSize, (int)Color * GM->PuyoSpriteSize, GM->PuyoSpriteSize, GM->PuyoSpriteSize));
}

sf::Vector2i Puyo::getCoordinate()
{
	return GridCoordinate;
}

PuyoColor Puyo::getColor()
{
	return Color;
}

bool Puyo::getDelete()
{
	return ToDelete;
}

void Puyo::setCoordinate(sf::Vector2i coord)
{
	GridCoordinate = coord;
	updatePosition();
}

void Puyo::setDelete(bool b)
{
	ToDelete = b;
}

void Puyo::setState(PuyoState ps)
{
	State = ps;
}

void Puyo::moveRight()
{
	GridCoordinate.x++;
	updatePosition();
}

void Puyo::moveLeft()
{
	GridCoordinate.x--;
	updatePosition();
}

void Puyo::fall()
{
	GridCoordinate.y++;
	updatePosition();
}

PuyoColor Puyo::randomColor()
{
	return PuyoColor(RandomInt(0, GameManager::getInstance()->QteColor));
}

void Puyo::Tick(float DeltaTime)
{
}
