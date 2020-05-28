#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include "SnakePart.h"
#include <vector>

#define START_LENGTH 4
#define START_DIRECTION 'r'
#define HEAD 0
#define TAIL (_length - 1)

#define HEAD_START_X 12
#define HEAD_START_Y 20


class Snake
{
public:
	Snake();
	~Snake();

	void turn(char direction);
	void updatePosition(bool border, int x, int y);
	void grow();

	Position getHeadPosition();
	std::vector<SnakePart> getSnakePosition();
	char getDirection();

private:
	std::vector<SnakePart> _body;
	char _direction;
	int _length;

	int _tailPreviousPositionX;
	int _tailPreviousPositionY;
};

#endif // SNAKE_H