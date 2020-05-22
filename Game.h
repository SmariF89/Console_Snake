#pragma once

#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include <iostream>
#include <thread>
#include <chrono>

class Game
{
public:
	Game();
	~Game();

	void start();
	bool& gameOver();
	void playerInput(char input);

private:
	void initialize();
	void progress();

	void score();

	char translateInput(char input);

	bool _gameOver;
	int _score;
	char _difficulty;
	Board* _board;
};

#endif // GAME_H