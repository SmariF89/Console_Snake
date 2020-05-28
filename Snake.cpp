#include "Snake.h"

/*
	Initial snake vector looks like this:
					 _									  _
	currentPosition	|  (12,20), (12,19), (12,18), (12,17)  |
	nextPosition	|_ (0 , 0), (12,20), (12,19), (12,18) _|
*/

Snake::Snake()
{
	_length = START_LENGTH;
	_direction = START_DIRECTION;
	
	// Initialized but not used in initial state.
	_tailPreviousPositionX = 0;
	_tailPreviousPositionY = 0;

	int bodyOffset = 1;
	for (int i = 0; i < _length; i++)
	{
		SnakePart snakePart;
		snakePart.currentPosition.x = HEAD_START_X;
		snakePart.currentPosition.y = HEAD_START_Y - i;
		
		// The head does not have a next position.
		if (i == 0) 
		{ 
			snakePart.nextPosition.x = 0;
			snakePart.nextPosition.y = 0;
		}
		else
		{
			snakePart.nextPosition.x = HEAD_START_X;
			snakePart.nextPosition.y = i == 1 ? HEAD_START_Y : HEAD_START_Y - bodyOffset++;
		}

		_body.push_back(snakePart);
	}
}

Snake::~Snake() {}

void Snake::turn(char direction)
{
	// Snake's internal input sanitization.
	// The snake cannot turn in its opposite direction.
	if (_direction == 'l' && direction == 'r') { return; }
	if (_direction == 'r' && direction == 'l') { return; }
	if (_direction == 'u' && direction == 'd') { return; }
	if (_direction == 'd' && direction == 'u') { return; }
	
	_direction = direction;
}

void Snake::updatePosition(bool border, int x, int y)
{
	// The head moves...
	if (border)
	{
		_body[HEAD].currentPosition.x = x;
		_body[HEAD].currentPosition.y = y;
	}
	else
	{
		switch (_direction)
		{
		case 'l':
			_body[HEAD].currentPosition.y -= 1;
			break;
		case 'r':
			_body[HEAD].currentPosition.y += 1;
			break;
		case 'u':
			_body[HEAD].currentPosition.x -= 1;
			break;
		case 'd':
			_body[HEAD].currentPosition.x += 1;
		}
	}

	_tailPreviousPositionX = _body[TAIL].currentPosition.x;
	_tailPreviousPositionY = _body[TAIL].currentPosition.y;

	// ...and the body will follow!
	for (int i = 1; i < _length; i++)
	{
		_body[i].currentPosition.x = _body[i].nextPosition.x;
		_body[i].currentPosition.y = _body[i].nextPosition.y;

		_body[i].nextPosition.x = _body[i - 1].currentPosition.x;
		_body[i].nextPosition.y = _body[i - 1].currentPosition.y;
	}
}

void Snake::grow()
{
	SnakePart addition;

	addition.currentPosition.x = _tailPreviousPositionX;
	addition.currentPosition.y = _tailPreviousPositionY;

	addition.nextPosition.x = _body[TAIL].currentPosition.x;
	addition.nextPosition.y = _body[TAIL].currentPosition.y;

	_body.push_back(addition);
	_length++;
}

Position Snake::getHeadPosition()
{
	return _body[HEAD].currentPosition;
}

std::vector<SnakePart> Snake::getSnakePosition()
{
	return _body;
}

char Snake::getDirection()
{
	return _direction;
}