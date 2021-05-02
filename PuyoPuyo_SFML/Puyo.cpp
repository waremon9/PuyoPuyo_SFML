#include "Puyo.h"
#include "Util.h"
#include "GameManager.h"
#include "RessourcesManager.h"

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
	GameManager* GM = GameManager::getInstance();
	RessourcesManager* RM = RessourcesManager::getInstance();

	_Sprite = new sf::Sprite();
	_Sprite->setPosition((sf::Vector2f)(GridCoordinate * GM->CellSize) + GM->GridPosition);
	_Sprite->setTexture(*RM->getTexture(RessourcesManager::PuyoSpriteSheet));
	_Sprite->setTextureRect(sf::IntRect((int)State * GM->PuyoSpriteSize, (int)Color * GM->PuyoSpriteSize, GM->PuyoSpriteSize, GM->PuyoSpriteSize));
	_Sprite->setScale(2,2);
}

PuyoColor Puyo::randomColor()
{
	return PuyoColor(RandomInt(0, static_cast<int>(PuyoColor::Count)));
}

void Puyo::Tick(float DeltaTime)
{
}
