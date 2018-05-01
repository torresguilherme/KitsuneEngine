#include "game.hpp"

int main()
{
	Game game(800, 600, "KE testing", KITSUNE_2D);
	while(!game.screen->isClosed)
	{
		game.run();
	}
	return 0;
}
