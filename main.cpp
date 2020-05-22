#include "Game.h"

#include <thread>

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

void playerInput(Game game)
{
	while (!game.gameOver())
	{
		if (((GetKeyState(w_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(w_lower) & short_msb_mask) == short_msb_mask))
			game.playerInput(input_w);
		if (((GetKeyState(a_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(a_lower) & short_msb_mask) == short_msb_mask))
			game.playerInput(input_a);
		if (((GetKeyState(s_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(s_lower) & short_msb_mask) == short_msb_mask))
			game.playerInput(input_s);
		if (((GetKeyState(d_upper) & short_msb_mask) == short_msb_mask) || ((GetKeyState(d_lower) & short_msb_mask) == short_msb_mask))
			game.playerInput(input_d);
	}
}

int main(int argc, char* argv[])
{
	Game game;
	std::thread playerInputThread(playerInput, std::ref(game));

	game.start();
	playerInputThread.join();
	return 0;
}