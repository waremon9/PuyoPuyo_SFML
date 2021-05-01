#pragma once
#include <vector>
#include "SFML/Graphics/VertexBuffer.hpp"

class Puyo;

class Grid
{
private:
	std::vector<Puyo*> _Grid;
	sf::Vector2f Size;

public:
	Grid(int, int);
	Grid(sf::Vector2f);

	sf::Vector2f getSize();
	Puyo* getElementAt(int, int);
	Puyo* getElementAt(sf::Vector2f);
};

