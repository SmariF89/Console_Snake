#include "Board.h"

#include <iostream>

Board::Board(bool* gameOver) 
{
	_board = new char* [BOARD_SIZE_VERTICAL];
	_gameOver = gameOver;

	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		_board[i] = new char[BOARD_SIZE_HORIZONTAL];
		for (int j = 0; j < BOARD_SIZE_HORIZONTAL; j++)
		{
			_board[i][j] = ' ';
		}
	}

	initializeBorders();
	initializeScore();
	
	_fruit = new Fruit(BOARD_SIZE_VERTICAL, BOARD_SIZE_HORIZONTAL);
	fruitManagementThread = new std::thread(&Board::fruitManager, this);
}

Board::~Board() 
{
	for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
	{
		delete _board[i];
	}

	fruitManagementThread->join();
	delete _board;
	delete _fruit;
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

void Board::initializeScore()
{
	std::lock_guard<std::mutex> guard(printMutex);

	setPrintPosition(SCORE_LABEL_POSITION_X, SCORE_LABEL_POSITION_Y);
	std::cout << "Your score: 0";

	setPrintPosition(0, 0);
	std::cout.flush();
}

void Board::moveSnake()
{
	Position currentSnakeHeadPosition = _snake.getHeadPosition();
	Position newSnakeHeadPosition;
	
	std::vector<SnakePart> currentSnakeBody = _snake.getSnakePosition();
	std::vector<SnakePart> newSnakeBody;

	char currentSnakeDirection = _snake.getDirection();
	char nextCellContent = ' ';
	char newCellContent = ' ';
	
	switch (currentSnakeDirection)
	{
	case 'l':
		nextCellContent = _board[currentSnakeHeadPosition.x][currentSnakeHeadPosition.y - 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, currentSnakeHeadPosition.x, BOARD_SIZE_HORIZONTAL - 2);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'r':
		nextCellContent = _board[currentSnakeHeadPosition.x][currentSnakeHeadPosition.y + 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, currentSnakeHeadPosition.x, 1);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'u':
		nextCellContent = _board[currentSnakeHeadPosition.x - 1][currentSnakeHeadPosition.y];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, BOARD_SIZE_VERTICAL - 2, currentSnakeHeadPosition.y);
		else
			_snake.updatePosition(false, 0, 0);
		break;

	case 'd':
		nextCellContent = _board[currentSnakeHeadPosition.x + 1][currentSnakeHeadPosition.y - 1];
		if (nextCellContent == BORDER_MATERIAL)
			_snake.updatePosition(true, 1, currentSnakeHeadPosition.y);
		else
			_snake.updatePosition(false, 0, 0);
		break;
	}
	
	newSnakeBody = _snake.getSnakePosition();
	newSnakeHeadPosition = newSnakeBody[0].currentPosition;
	
	newCellContent = _board[newSnakeHeadPosition.x][newSnakeHeadPosition.y];
	if (newCellContent == FRUIT_MATERIAL)
	{
		_hitFruit = true;
	}
	
	printSnake(currentSnakeBody, newSnakeBody);
}

bool Board::hitFruit()
{
	bool result = _hitFruit;
	if (_hitFruit) { _hitFruit = false; }
	return result;
}

void Board::updateScore(int score)
{
	printScore(score);
}

void Board::redirectSnake(char direction)
{
	// TODO: Move all sanity checks to one place.
	if (_snake.getDirection() == direction)
		return;

	_snake.turn(direction);
}

void Board::fruitManager()
{
	while (!*_gameOver)
	{
		spawnFruit();
		std::this_thread::sleep_for(std::chrono::milliseconds(FRUIT_DELAY));
	}
}

void Board::spawnFruit()
{
	std::lock_guard<std::mutex> guard(printMutex);

	Position oldFruitPosition = _fruit->getPosition();
	_fruit->spawn();
	Position newFruitPosition = _fruit->getPosition();

	_board[newFruitPosition.x][newFruitPosition.y] = FRUIT_MATERIAL;
	
	printFruit(oldFruitPosition, newFruitPosition);
}

void Board::printBoard()
{
	std::lock_guard<std::mutex> guard(printMutex);

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

void Board::printSnake(std::vector<SnakePart> oldBody, std::vector<SnakePart> newBody)
{
	std::lock_guard<std::mutex> guard(printMutex);

	for (size_t i = 0; i < oldBody.size(); i++)
	{
		setPrintPosition(oldBody[i].currentPosition.x, oldBody[i].currentPosition.y);
		std::cout << ' ';
	
		setPrintPosition(newBody[i].currentPosition.x, newBody[i].currentPosition.y);
		std::cout << SNAKE_MATERIAL;
	}

	std::cout.flush();
}

void Board::printFruit(Position oldPosition, Position newPosition)
{
	setPrintPosition(oldPosition.x, oldPosition.y);
	std::cout << ' ';

	setPrintPosition(newPosition.x, newPosition.y);
	std::cout << FRUIT_MATERIAL;

	std::cout.flush();
}

void Board::printScore(int score)
{
	std::lock_guard<std::mutex> guard(printMutex);

	setPrintPosition(SCORE_POSITION_X, SCORE_POSITION_Y);
	std::cout << score;

	std::cout.flush();
}

void Board::setPrintPosition(int x, int y)
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)y, (SHORT)x };
	SetConsoleCursorPosition(outputHandle, coord);
}