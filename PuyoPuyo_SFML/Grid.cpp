#include "Grid.h"
#include "Puyo.h"
#include "GameManager.h"
#include <iostream>

Grid::Grid(int x, int y, int cell, sf::Vector2f pos)
{
	_Grid.resize(x * y, nullptr);
	Dimension = sf::Vector2i(x, y);
	Cellsize = cell;
	Position = pos;

	createGridGraphic();
}

Grid::Grid(sf::Vector2i dim, int cell, sf::Vector2f pos)
{
	_Grid.resize(dim.x * dim.y, nullptr);
	Dimension = dim;
	Cellsize = cell;
	Position = pos;

	createGridGraphic();
}

void Grid::createGridGraphic()
{
	for (int i = 0; i <= Dimension.x; i++) {
		sf::RectangleShape* temp = new sf::RectangleShape(sf::Vector2f(1,Cellsize * Dimension.y));
		temp->setPosition(Position + sf::Vector2f(i * Cellsize,0));
		GridGraphic.push_back(temp);
	}

	for (int j = 0; j <= Dimension.y; j++) {
		sf::RectangleShape* temp = new sf::RectangleShape(sf::Vector2f(Cellsize * Dimension.x, 1));
		temp->setPosition(Position + sf::Vector2f(0, j * Cellsize));
		GridGraphic.push_back(temp);
	}
}

sf::Vector2i Grid::getDimension()
{
	return Dimension;
}

void Grid::addElementAt(int x, int y, Puyo* p)
{
	_Grid[y * Dimension.x + x] = p;
}

void Grid::addElementAt(sf::Vector2i coord, Puyo* p)
{
	_Grid[coord.y * Dimension.x + coord.x] = p;
}

Puyo* Grid::getElementAt(int x, int y)
{
	return _Grid[y * Dimension.x + x];
}

Puyo* Grid::getElementAt(sf::Vector2i coord)
{
	return _Grid[coord.y * Dimension.x + coord.x];
}

void Grid::Draw()
{
	GameManager* GM = GameManager::getInstance();
	for (sf::RectangleShape* rs : GridGraphic)
	{
		GM->drawOnWindow(rs);
	}
}
