#include "breakout.hpp"

int main()
{
	Game game(800, 600, "Breakout", KITSUNE_2D);

	CollisionLayer c;
	initGame(game, c);
	gameLoop(game, c);
	return 0;
}
