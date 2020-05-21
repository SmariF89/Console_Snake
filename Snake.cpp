#include "Snake.h"

#define MAX_SNAKE_LENGTH 20;
#define SNAKE_MATERIAL '*';

Snake::Snake()
{
	_head = SNAKE_MATERIAL;
	_length = 1;
	_maxLength = MAX_SNAKE_LENGTH;
	_position.x = 12;
	_position.y = 20;
	_direction = 'd';
}

Snake::~Snake() {}

void Snake::turn(char direction)
{
	// TODO: Sanity check input.

	_direction = direction;
}

void Snake::updatePosition(bool border, int x, int y)
{
	if (border)
	{
		_position.x = x;
		_position.y = y;
	}
	else
	{
		switch (_direction)
		{
		case 'l':
			_position.y -= 1;
			break;
		case 'r':
			_position.y += 1;
			break;
		case 'u':
			_position.x -= 1;
			break;
		case 'd':
			_position.x += 1;
		}
	}
}

// NOTE: Not used in alpha.
void Snake::grow()
{
	_length++;
}

Position Snake::getPosition()
{
	return _position;
}

char Snake::getDirection()
{
	return _direction;
}