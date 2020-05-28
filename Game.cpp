#include "Game.h"

Game::Game() 
{
	_gameOver = false;
	_score = 0;
	_difficulty = 'm';
}

Game::~Game() 
{
	delete _board;
}

void Game::start()
{
	initialize();
	_board->printBoard();
	while (!_gameOver)
	{
		progress();
	}
}

void Game::initialize()
{
	if (_board != nullptr)
		delete _board;
	
	_board = new Board(&_gameOver);
}

void Game::progress()
{
	_board->moveSnake();
	if (_board->hitFruit()) { score(); }
	if (_board->hitSnake()) 
	{ 
		_gameOver = true;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::score()
{
	_score += SCORE_AMOUNT;
	_board->updateScore(_score);
}

bool& Game::gameOver()
{
	return _gameOver;
}

void Game::playerInput(char input)
{
	char translatedInput = this->translateInput(input);
	if (translatedInput == 'u' ||
		translatedInput == 'l' ||
		translatedInput == 'd' ||
		translatedInput == 'r')
		_board->redirectSnake(translatedInput);
}

char Game::translateInput(char input)
{
	if (input == 'W' || input == 'w') { return 'u'; }
	if (input == 'A' || input == 'a') { return 'l'; }
	if (input == 'S' || input == 's') { return 'd'; }
	if (input == 'D' || input == 'd') { return 'r'; }
	return ' ';
}