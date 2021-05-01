#include "Grid.h"
#include "Puyo.h"

Grid::Grid(int x, int y)
{
	_Grid.resize(x * y, nullptr);
	Size = sf::Vector2f(x, y);
}

Grid::Grid(sf::Vector2f size)
{

	_Grid.resize(size.x * size.y, nullptr);
	Size = size;
}

sf::Vector2f Grid::getSize()
{
	return Size;
}

Puyo* Grid::getElementAt(int x, int y)
{
	return _Grid[y * Size.x + x];
}

Puyo* Grid::getElementAt(sf::Vector2f s)
{
	return _Grid[s.y * Size.x + s.x];
}
