#include "Grid.h"
#include "Puyo.h"
#include "GameManager.h"
#include <iostream>
#include "Util.h"

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

void Grid::removeElementAt(int x, int y)
{
	_Grid[y * Dimension.x + x] = nullptr;
}

void Grid::removeElementAt(sf::Vector2i coord)
{
	_Grid[coord.y * Dimension.x + coord.x] = nullptr;
}

//Return pointer to adjacent puyo. no puyo and out of grid is nullptr
std::vector<Puyo*> Grid::getAdjacentPuyo(Puyo* p)
{
	std::vector<Puyo*> adjPuyo;

	if (p->getCoordinate().x > 0) {//left from actual
		adjPuyo.push_back(getElementAt(p->getCoordinate() + sf::Vector2i(-1, 0)));
	}
	else adjPuyo.push_back(nullptr);
	if (p->getCoordinate().y > 0) {//up from actual
		adjPuyo.push_back(getElementAt(p->getCoordinate() + sf::Vector2i(0, -1)));
	}
	else adjPuyo.push_back(nullptr);
	if (p->getCoordinate().x < Dimension.x - 1) {//right from actual
		adjPuyo.push_back(getElementAt(p->getCoordinate() + sf::Vector2i(1, 0)));
	}
	else adjPuyo.push_back(nullptr);
	if (p->getCoordinate().y < Dimension.y - 1) {//down from actual
		adjPuyo.push_back(getElementAt(p->getCoordinate() + sf::Vector2i(0, 1)));
	}
	else adjPuyo.push_back(nullptr);

	return adjPuyo;
}

bool Grid::MakePuyoFall()
{
	bool endOfWork = true;
	for (int i = _Grid.size() - 1 - Dimension.x; i >= 0; i--) {
		if (_Grid[i] != nullptr && _Grid[i + Dimension.x] == nullptr) {
			_Grid[i]->fall();
			_Grid[i + Dimension.x] = _Grid[i];
			_Grid[i] = nullptr;

			endOfWork = false;
		}
	}

	for (Puyo* puyo : _Grid) {
		if(puyo) DeterminePuyoState(puyo);
	}

	return endOfWork;
}

bool Grid::CheckForGroup()
{
	bool group = false;
	std::vector<Puyo*> CheckedPuyo;
	std::vector<Puyo*> ToCheck;
	Puyo* Actual;
	std::vector<Puyo*> ActualGroup;

	for (Puyo* p : _Grid) {
		if (p != nullptr && !ContainPuyo(CheckedPuyo, p)) {

			ToCheck.push_back(p);
			ActualGroup.clear();

			while (!ToCheck.empty())
			{
				Actual = ToCheck.back();
				ToCheck.pop_back();

				if (!ContainPuyo(CheckedPuyo, Actual)) {

					ActualGroup.push_back(Actual);

					for (Puyo* adjacent : getAdjacentPuyo(Actual)) {
						if (adjacent != nullptr && adjacent->getColor() == Actual->getColor() && !ContainPuyo(CheckedPuyo, adjacent)) {
							ToCheck.push_back(adjacent);
						}
					}

					CheckedPuyo.push_back(Actual);
				}
			}
			if (ActualGroup.size() >= 4) {
				group = true;
				for (Puyo* puyo : ActualGroup) {
					puyo->setDelete(true);
				}
			}
		}
	}
	return group;
}

void Grid::DeterminePuyoState(Puyo* p)
{
	bool UP = false, LEFT = false, DOWN = false, RIGHT = false;

	std::vector<Puyo*> adjPuyo = getAdjacentPuyo(p);

	if (adjPuyo[0] != nullptr && adjPuyo[0]->getColor() == p->getColor()) LEFT = true;
	if (adjPuyo[1] != nullptr && adjPuyo[1]->getColor() == p->getColor()) UP = true;
	if (adjPuyo[2] != nullptr && adjPuyo[2]->getColor() == p->getColor()) RIGHT = true;
	if (adjPuyo[3] != nullptr && adjPuyo[3]->getColor() == p->getColor()) DOWN = true;

	if (!UP && !RIGHT && !DOWN && !LEFT) p->setState(PuyoState::Neutral);
	if (UP && !RIGHT && !DOWN && !LEFT) p->setState(PuyoState::N);
	if (!UP && RIGHT && !DOWN && !LEFT) p->setState(PuyoState::E);
	if (!UP && !RIGHT && DOWN && !LEFT) p->setState(PuyoState::S);
	if (!UP && !RIGHT && !DOWN && LEFT) p->setState(PuyoState::W);
	if (UP && !RIGHT && DOWN && !LEFT) p->setState(PuyoState::SN);
	if (!UP && RIGHT && !DOWN && LEFT) p->setState(PuyoState::EW);
	if (UP && RIGHT && !DOWN && !LEFT) p->setState(PuyoState::NE);
	if (UP && !RIGHT && !DOWN && LEFT) p->setState(PuyoState::NW);
	if (!UP && RIGHT && DOWN && !LEFT) p->setState(PuyoState::SE);
	if (!UP && !RIGHT && DOWN && LEFT) p->setState(PuyoState::SW);
	if (UP && RIGHT && DOWN && !LEFT) p->setState(PuyoState::SNE);
	if (UP && RIGHT && !DOWN && LEFT) p->setState(PuyoState::NEW);
	if (UP && !RIGHT && DOWN && LEFT) p->setState(PuyoState::SNW);
	if (!UP && RIGHT && DOWN && LEFT) p->setState(PuyoState::SEW);
	if (UP && RIGHT && DOWN && LEFT) p->setState(PuyoState::NSEW);

	p->updateSpriteRect();
}

void Grid::Draw()
{
	GameManager* GM = GameManager::getInstance();
	for (sf::RectangleShape* rs : GridGraphic)
	{
		GM->drawOnWindow(rs);
	}
}
