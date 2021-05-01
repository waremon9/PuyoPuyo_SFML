#pragma once
#include "Entity.h"
#include "SFML/Graphics/VertexBuffer.hpp"

class Puyo : Entity
{
private:
	sf::Vector2f GridCoordinate;

public:
	Puyo();
	Puyo(int x, int y);
	Puyo(sf::Vector2f coord);

	void Tick(float DeltaTime) override;
};

