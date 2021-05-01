#include "Puyo.h"

Puyo::Puyo()
{
	GridCoordinate = sf::Vector2f(0, 0);
}

Puyo::Puyo(int x, int y)
{
	GridCoordinate = sf::Vector2f(x, y);
}

Puyo::Puyo(sf::Vector2f coord)
{
	GridCoordinate = coord;
}

void Puyo::Tick(float DeltaTime)
{
}
