#include "breakout.hpp"

int main()
{
	Game game(800, 600, "Breakout", KITSUNE_2D);

	initGame(game);
	gameLoop(game);
	return 0;
}
