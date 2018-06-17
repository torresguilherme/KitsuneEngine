#include "game.hpp"

const int S_HEIGHT = 900;
const int S_WIDTH = 1600;

int main()
{
	Game game(S_WIDTH, S_HEIGHT, "KE testing", KITSUNE_3D);
	//instantiate player
	Node *player = new Node();
	game.root->addChild(player);
	player->mesh = loadMesh("../res/meshes/tank.obj");
	player->texture = loadTexture("../res/textures/camouflage.jpg");
	float playerSpeed = 0.1;

	// instantiate arena
	StaticBody *ground = new StaticBody();
	game.root->addChild(ground);
	ground->addCollider(ground->BOX_COL);
	ground->mesh = loadMesh("../res/meshes/arena.obj");
	ground->texture = loadTexture("../res/textures/rocks.jpeg");

	// initialize input
	game.input->insertNewAction("up", SDL_SCANCODE_W);
	game.input->insertNewAction("down", SDL_SCANCODE_S);
	game.input->insertNewAction("left", SDL_SCANCODE_A);
	game.input->insertNewAction("right", SDL_SCANCODE_D);

	while(!game.screen->isClosed)
	{
		// update player rotation
		int x, y;
		game.input->getMousePos(&x, &y);
		x -= S_WIDTH/2;
		float fx = (float)x/1600.0;
		y -= S_HEIGHT/2;
		float fy = (float)y/900.0;
		player->setRot(0.0, cosf((float)fx) + sinf((float)fy), 0.0);

		// update player and camera position
		if(game.input->isActionPressed("up"))
		{
			player->setPos(player->getPos().x, player->getPos().y, player->getPos().z + playerSpeed);
		}

		// update player shooting
		// instantiate enemies
		// update enemy positions
		// update bullet physics
		game.run();
	}
	return 0;
}
