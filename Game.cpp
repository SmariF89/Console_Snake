#include "Game.h"

Game::Game() 
{
	_gameOver = false;
	_score = 0;
	_difficulty = 'm';

	playerInputThread = new std::thread(&Game::playerInput, this);
}

Game::~Game() 
{
	delete _board;
	playerInputThread->join();
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
	if (_board->hitSnake()) { _gameOver = true; }
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::score()
{
	_score += SCORE_AMOUNT;
	_board->updateScore(_score);
}

void Game::affectGame(char input)
{
	char translatedInput = this->translateInput(input);
	if (translatedInput == 'u' ||
		translatedInput == 'l' ||
		translatedInput == 'd' ||
		translatedInput == 'r')
		_board->redirectSnake(translatedInput);
}

void Game::playerInput()
{
	while (!_gameOver)
	{
		if (((GetKeyState(w_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(w_lower) & short_msb_mask) == short_msb_mask))
			affectGame(input_w);
		if (((GetKeyState(a_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(a_lower) & short_msb_mask) == short_msb_mask))
			affectGame(input_a);
		if (((GetKeyState(s_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(s_lower) & short_msb_mask) == short_msb_mask))
			affectGame(input_s);
		if (((GetKeyState(d_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(d_lower) & short_msb_mask) == short_msb_mask))
			affectGame(input_d);
	}
}

char Game::translateInput(char input)
{
	if (input == 'W' || input == 'w') { return 'u'; }
	if (input == 'A' || input == 'a') { return 'l'; }
	if (input == 'S' || input == 's') { return 'd'; }
	if (input == 'D' || input == 'd') { return 'r'; }
	return ' ';
}