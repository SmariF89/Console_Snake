#include "Board.h"

#include <iostream>

Board::Board() 
{
	_board = new char* [BOARD_SIZE_VERTICAL];

	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		_board[i] = new char[BOARD_SIZE_HORIZONTAL];
		for (int j = 0; j < BOARD_SIZE_HORIZONTAL; j++)
		{
			_board[i][j] = ' ';
		}
	}

	initializeBorders();
}

Board::~Board() 
{
	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		delete _board[i];
	}
	delete _board;
}

void Board::initializeBorders()
{
	// Vertical border lines
	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		_board[i][0] = BORDER_MATERIAL;
		_board[i][BOARD_SIZE_HORIZONTAL - 1] = BORDER_MATERIAL;
	}

	// Horizontal border lines
	for (int i = 0; i < BOARD_SIZE_HORIZONTAL; i++)
	{
		_board[0][i] = BORDER_MATERIAL;
		_board[BOARD_SIZE_VERTICAL - 1][i] = BORDER_MATERIAL;
	}
}

void Board::moveSnake()
{
	Position currentSnakePosition = _snake.getPosition();
	Position newSnakePosition;
	char currentSnakeDirection = _snake.getDirection();
	char nextCellContent = ' ';
	
	switch (currentSnakeDirection)
	{
	case 'l':
		nextCellContent = _board[currentSnakePosition.x][currentSnakePosition.y - 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, currentSnakePosition.x, BOARD_SIZE_HORIZONTAL - 2);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'r':
		nextCellContent = _board[currentSnakePosition.x][currentSnakePosition.y + 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, currentSnakePosition.x, 1);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'u':
		nextCellContent = _board[currentSnakePosition.x - 1][currentSnakePosition.y];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, BOARD_SIZE_VERTICAL - 2, currentSnakePosition.y);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'd':
		nextCellContent = _board[currentSnakePosition.x + 1][currentSnakePosition.y - 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, 1, currentSnakePosition.y);
		else
			_snake.updatePosition(false, 0, 0);
		break;
	}
	
	newSnakePosition = _snake.getPosition();
	printSnake(currentSnakePosition, newSnakePosition);
}

void Board::redirectSnake(char direction)
{
	if (_snake.getDirection() == direction)
		return;

	_snake.turn(direction);
}

void Board::printBoard()
{
	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		for (int j = 0; j < BOARD_SIZE_HORIZONTAL; j++)
		{
			std::cout << _board[i][j];
		}
		std::cout << std::endl;
	}
	std::cout.flush();
}

void Board::printSnake(Position oldPosition, Position newPosition)
{
	setPrintPosition(oldPosition.x, oldPosition.y);
	std::cout << ' ';
	
	setPrintPosition(newPosition.x, newPosition.y);
	std::cout << SNAKE_MATERIAL;

	std::cout.flush();
}

void Board::setPrintPosition(int x, int y)
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)y, (SHORT)x };
	SetConsoleCursorPosition(outputHandle, coord);
}