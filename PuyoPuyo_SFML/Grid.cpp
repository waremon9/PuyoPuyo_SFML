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

					if (Actual->getCoordinate().x > 0) {//left from actual
						Puyo* left = getElementAt(Actual->getCoordinate() + sf::Vector2i(-1, 0));
						//exist? same color? not already done?
						if (left != nullptr && left->getColor() == Actual->getColor() && !ContainPuyo(CheckedPuyo, left)) {
							ToCheck.push_back(left);
						}
					}
					if (Actual->getCoordinate().y > 0) {//up from actual
						Puyo* up = getElementAt(Actual->getCoordinate() + sf::Vector2i(0, -1));
						if (up != nullptr && up->getColor() == Actual->getColor() && !ContainPuyo(CheckedPuyo, up)) {
							ToCheck.push_back(up);
						}
					}
					if (Actual->getCoordinate().x < Dimension.x - 1) {//right from actual
						Puyo* right = getElementAt(Actual->getCoordinate() + sf::Vector2i(1, 0));
						if (right != nullptr && right->getColor() == Actual->getColor() && !ContainPuyo(CheckedPuyo, right)) {
							ToCheck.push_back(right);
						}
					}
					if (Actual->getCoordinate().y < Dimension.y - 1) {//down from actual
						Puyo* down = getElementAt(Actual->getCoordinate() + sf::Vector2i(0, 1));
						if (down != nullptr && down->getColor() == Actual->getColor() && !ContainPuyo(CheckedPuyo, down)) {
							ToCheck.push_back(down);
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

void Grid::Draw()
{
	GameManager* GM = GameManager::getInstance();
	for (sf::RectangleShape* rs : GridGraphic)
	{
		GM->drawOnWindow(rs);
	}
}
