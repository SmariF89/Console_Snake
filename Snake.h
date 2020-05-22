#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include "Position.h"

class Snake
{
public:
	Snake();
	~Snake();

	void turn(char direction);
	void updatePosition(bool border, int x, int y);
	void grow();

	Position getPosition();
	char getDirection();

private:
	char _head;
	int _length;
	int _maxLength;

	Position _position;

	char _direction;
};

#endif // SNAKE_H