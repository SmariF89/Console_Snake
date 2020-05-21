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

private:
	void initialize();
	void progress();

	void score();
	bool gameOver();

	void playerInput();

	int _score;
	int _difficulty;
	Board* _board;

	std::thread* inputThread;
};

#endif // GAME_H