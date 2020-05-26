#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Fruit.h"
#include "Position.h"
#include "SnakePart.h"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>


#define BOARD_SIZE_VERTICAL 25
#define BOARD_SIZE_HORIZONTAL 50

#define SNAKE_MATERIAL '*'
#define FRUIT_MATERIAL 'Q'
#define BORDER_MATERIAL '#'

#define SCORE_LABEL_POSITION_X (BOARD_SIZE_VERTICAL + 2)
#define SCORE_LABEL_POSITION_Y 0
#define SCORE_POSITION_X	   (BOARD_SIZE_VERTICAL + 2)
#define SCORE_POSITION_Y	   12

#define FRUIT_DELAY 5000

class Board
{
public:
	Board(bool* gameOver);
	~Board();

	void moveSnake();
	bool hitFruit();
	void updateScore(int score);
	void redirectSnake(char direction);
	void printBoard();

private:
	void initializeBorders();
	void initializeScore();
	void fruitManager();
	void spawnFruit();

	void printSnake(std::vector<SnakePart> oldBody, std::vector<SnakePart> newBody);
	void printFruit(Position oldPosition, Position newPosition);
	void printScore(int score);
	void setPrintPosition(int x, int y);

	bool* _gameOver;
	bool _hitFruit;
	std::thread* fruitManagementThread;
	std::mutex printMutex;

	Snake _snake;
	Fruit* _fruit;
	char** _board;
};

#endif // BOARD_H