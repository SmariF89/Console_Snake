#include "Game.h"

Game::Game() 
{
	inputThread = new std::thread(this->playerInput);
}

Game::~Game() 
{
	delete _board;
	inputThread->join();
	delete inputThread;
}

void Game::start()
{
	initialize();
	_board->printBoard();
	while (!gameOver())
	{
		progress();
	}
}

void Game::initialize()
{
	if (_board != nullptr)
		delete _board;
	
	_board = new Board();
	_score = 0;
}

void Game::progress()
{
	_board->moveSnake();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::score()
{
	_score++;
}

bool Game::gameOver()
{
	return false;
}

void Game::playerInput()
{
	while(!gameOver())
	{
		char input;
		std::cin >> input;

		if (input == 'w' || input == 'a' || input == 's' || input == 'd')
		{
			_board->redirectSnake(input);
		}
	}
}