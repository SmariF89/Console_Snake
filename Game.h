#pragma once

#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include <thread>
#include <chrono>

/* ------ INPUT CONSTANTS -------- */

#define w_upper 87
#define w_lower 119
#define a_upper 65
#define a_lower 97
#define s_upper 83
#define s_lower 115
#define d_upper 68
#define d_lower 100

#define short_msb_mask 128

#define input_w 'w'
#define input_a 'a'
#define input_s 's'
#define input_d 'd'

/* ---------------------------------- */

#define SCORE_AMOUNT 2
#define SPEED_INITIAL 150
#define SPEED_MAX 25
#define SPEED_DIFF 5

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
	void increaseSpeed();

	void affectGame(char input);
	void playerInput();
	char translateInput(char input);

	bool _gameOver;
	int _score;
	int _speed;
	char _difficulty;
	Board* _board;

	std::thread* playerInputThread;
};

#endif // GAME_H