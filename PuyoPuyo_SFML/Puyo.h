#pragma once
#include "Entity.h"
#include "SFML/Graphics/VertexBuffer.hpp"
#include <map>

enum class PuyoColor{
	Red, Gree, Blue, Yellow, Purple, Pink, Cyan, Garbage, Count
};
enum class PuyoState {
	Neutral, S, N, SN, E, SE, NE, SNE, W, SW, NW, SNW, EW, SEW, NEW, NSEW, Death1, Body, Eyes, Death2, Count
};

class Puyo : public Entity
{
private:
	sf::Vector2i GridCoordinate;
	PuyoColor Color;
	PuyoState State;

	PuyoColor randomColor();
public:
	Puyo();
	Puyo(int x, int y);
	Puyo(sf::Vector2i coord);

	void setSpriteInfo();
	void updatePosition();

	void moveRight(int i);
	void fall();

	void Tick(float DeltaTime) override;
};