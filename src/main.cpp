#include "game.hpp"
#include "breakout.hpp"

int main()
{
	Game game(800, 600, "Breakout", KITSUNE_2D);
	
	Rect2D player(0.25, 0.25, 1.0, 0.0, 0.0, 1.0);
	game.root2d->addChild(&player);

	game.run();
	return 0;
}
