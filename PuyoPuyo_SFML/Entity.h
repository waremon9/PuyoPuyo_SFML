#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
protected:
	sf::Sprite* _Sprite;
	sf::Vector2f Position;

public:
	Entity();

	sf::Vector2f getPosition();
	sf::Sprite* getSprite();

	virtual void Tick(float DeltaTime) = 0;
	virtual void Draw();
};

