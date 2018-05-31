#include "game.hpp"

int main()
{
	Game game(800, 600, "KE testing", KITSUNE_3D);
	game.root->mesh = loadMesh("../res/meshes/monkey.obj");
	while(!game.screen->isClosed)
	{
		game.run();
	}
	return 0;
}
