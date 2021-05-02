#include "Puyo.h"
#include "Util.h"

Puyo::Puyo()
{
	GridCoordinate = sf::Vector2f(0, 0);
	State = PuyoState::Neutral;
	Color = PuyoColor::Red;
}

Puyo::Puyo(int x, int y)
{
	GridCoordinate = sf::Vector2f(x, y);
	State = PuyoState::Neutral;
	Color = randomColor();
}

Puyo::Puyo(sf::Vector2f coord)
{
	GridCoordinate = coord;
	State = PuyoState::Neutral;
	Color = randomColor();
}

PuyoColor Puyo::randomColor()
{
	return PuyoColor(RandomInt(0, static_cast<int>(PuyoColor::Count)));
}

void Puyo::Tick(float DeltaTime)
{
}
