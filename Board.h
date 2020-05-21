#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Position.h"

#include <iostream>
#include <Windows.h>


#define BOARD_SIZE_VERTICAL 25
#define BOARD_SIZE_HORIZONTAL 50

#define SNAKE_MATERIAL '*'
#define BORDER_MATERIAL '#'

class Board
{
public:
	Board();
	~Board();

	void moveSnake();
	void redirectSnake(char direction);
	void printBoard();

private:
	void initializeBorders();

	void printSnake(Position oldPosition, Position newPosition);
	void setPrintPosition(int x, int y);

	Snake _snake;
	char** _board;
};

#endif // BOARD_H