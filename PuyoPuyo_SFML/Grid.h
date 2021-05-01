#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Puyo;

class Grid
{
private:
	std::vector<Puyo*> _Grid;
	sf::Vector2i Dimension;
	float Cellsize;
	sf::Vector2f Position;
	std::vector<sf::RectangleShape*> GridGraphic;

public:
	Grid(int x, int y, int cell, sf::Vector2f pos);
	Grid(sf::Vector2i dim, int cell, sf::Vector2f pos);
	void createGridGraphic();

	sf::Vector2i getDimension();
	Puyo* getElementAt(int, int);
	Puyo* getElementAt(sf::Vector2i);

	void Draw();
};

