#include "game.hpp"
#include "breakout.hpp"

int main()
{
	Game game(800, 600, "Breakout", KITSUNE_2D);
	
	// init player
	Rect2D player(0.25, 0.1, 1.0, 0.0, 0.0, 1.0);
	player.setPos(0.0, -0.8);
	game.root2d->addChild(&player);

	// init ball
	Rect2D ball(0.05, 0.05, 0.0, 1.0, 0.0, 1.0);
	game.root2d->addChild(&ball);

	// init bricks

	while(!game.screen->isClosed)
	{
		// update player input
		// update player movement
		// update ball movement w/ collision
		game.run();
	}

	return 0;
}
