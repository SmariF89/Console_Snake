#pragma once

#ifndef FRUIT_H
#define FRUIT_H

#include "Position.h"

#include <stdlib.h>
#include <time.h>

#define DEFAULT_SCORE 10
#define DEFAULT_TIME 10

class Fruit
{
public:
	Fruit(int boardVerticalSize, int boardHorizontalSize);
	~Fruit();

	void spawn();
	Position getPosition();

private:
	void vanish();
	int getRandomCoordinate(bool x);

	int _score;
	int _timeLeft;

	int _maxCoordinateX;
	int _maxCoordinateY;

	Position _position;
};

#endif // FRUIT_H