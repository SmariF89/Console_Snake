#include "Fruit.h"

Fruit::Fruit(int boardVerticalSize, int boardHorizontalSize)
{
	_position.x = 3;
	_position.y = 3;
	_maxCoordinateX = boardVerticalSize - 3;
	_maxCoordinateY = boardHorizontalSize - 3;
}
Fruit::~Fruit() {}

void Fruit::spawn()
{
	_position.x = getRandomCoordinate(true);
	_position.y = getRandomCoordinate(false);
}

Position Fruit::getPosition()
{
	return _position;
}

void Fruit::vanish()
{

}

int Fruit::getRandomCoordinate(bool x)
{
	srand(time(NULL));
	return rand() % (x ? _maxCoordinateX : _maxCoordinateY) + 2;
}