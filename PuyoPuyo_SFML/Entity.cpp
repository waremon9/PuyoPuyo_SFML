#include "Entity.h"
#include "GameManager.h"

Entity::Entity()
{
	_Sprite = nullptr;
	Position = sf::Vector2f(0, 0);
}

sf::Vector2f Entity::getPosition()
{
	return Position;
}

sf::Sprite* Entity::getSprite()
{
	return _Sprite;
}

void Entity::Draw()
{
	GameManager::getInstance()->drawOnWindow(_Sprite);
}
