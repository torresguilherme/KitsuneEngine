#include "breakout.hpp"

int main()
{
	Game game(800, 600, "Breakout", KITSUNE_2D);

	CollisionLayer c;
	initGame(game, c, 3);
	gameLoop(game, c, 3);
	return 0;
}
