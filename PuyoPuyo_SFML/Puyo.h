#pragma once
#include "Entity.h"
#include "SFML/Graphics/VertexBuffer.hpp"

enum class PuyoColor
{
	Red,
	Green,
	Blue,
	Yellow,
	Purple,
	Pink,
	Cyan
};

class Puyo : Entity
{
private:
	sf::Vector2f GridCoordinate;
	PuyoColor Color;

public:
	Puyo();
	Puyo(int x, int y);
	Puyo(sf::Vector2f coord);

	void Tick(float DeltaTime) override;
};

