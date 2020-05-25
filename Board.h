#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Fruit.h"
#include "Position.h"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <chrono>


#define BOARD_SIZE_VERTICAL 25
#define BOARD_SIZE_HORIZONTAL 50

#define SNAKE_MATERIAL '*'
#define FRUIT_MATERIAL 'Q'
#define BORDER_MATERIAL '#'

class Board
{
public:
	Board(bool* gameOver);
	~Board();

	void moveSnake();
	void redirectSnake(char direction);
	void printBoard();

private:
	void initializeBorders();
	void fruitManager();
	void spawnFruit();

	void printSnake(Position oldPosition, Position newPosition);
	void printFruit(Position oldPosition, Position newPosition);
	void setPrintPosition(int x, int y);

	bool* _gameOver;
	std::thread* fruitManagementThread;
	std::mutex printMutex;

	Snake _snake;
	Fruit* _fruit;
	char** _board;
};

#endif // BOARD_H