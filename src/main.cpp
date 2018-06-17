#include "game.hpp"

using namespace std;
const int S_HEIGHT = 600;
const int S_WIDTH = 1040;

int main()
{
	Game game(S_WIDTH, S_HEIGHT, "KE testing", KITSUNE_3D);
	//instantiate player
	KinematicBody *player = new KinematicBody();
	game.root->addChild(player);
	player->mesh = loadMesh("../res/meshes/tank.obj");
	player->texture = loadTexture("../res/textures/camouflage.jpg");
	float playerSpeed = 0.1;
	player->setPos(player->getPos().x, player->getPos().y + 0.5, player->getPos().z);

	Node *shootPoint = new Node();
	player->addChild(shootPoint);
	shootPoint->transform.translation = glm::vec3(0.0, 0.0, 2.0);
	float bulletSpeed = 0.5;

	vector<glm::vec3> directions;
	vector<float> distances;

	// instantiate arena
	StaticBody *ground = new StaticBody();
	game.root->addChild(ground);
	ground->addCollider(ground->BOX_COL, game.layer0);
	ground->mesh = loadMesh("../res/meshes/arena.obj");
	ground->texture = loadTexture("../res/textures/rocks.jpeg");

	// initialize input
	game.input->insertNewAction("up", SDL_SCANCODE_W);
	game.input->insertNewAction("down", SDL_SCANCODE_S);
	game.input->insertNewAction("left", SDL_SCANCODE_A);
	game.input->insertNewAction("right", SDL_SCANCODE_D);
	game.input->insertNewAction("shoot", SDL_SCANCODE_RETURN);

	while(!game.screen->isClosed)
	{
		// update player and camera position
		if(game.input->isActionPressed("up"))
		{
			player->setPos(player->getPos().x + (playerSpeed * sinf(player->getRot().y)), player->getPos().y, player->getPos().z + (playerSpeed * cosf(player->getRot().y)));
		}
		if(game.input->isActionPressed("down"))
		{
			player->setPos(player->getPos().x - (playerSpeed * sinf(player->getRot().y)), player->getPos().y, player->getPos().z - (playerSpeed * cosf(player->getRot().y)));
		}
		if(game.input->isActionPressed("left"))
		{
			player->setRot(player->getRot().x, player->getRot().y + playerSpeed, player->getRot().z);
		}
		if(game.input->isActionPressed("right"))
		{
			player->setRot(player->getRot().x, player->getRot().y - playerSpeed, player->getRot().z);
		}
		if(player->getPos().x > 8.0)
			player->setPos(8.0, player->getPos().y, player->getPos().z);
		if(player->getPos().x < -8.0)
			player->setPos(-8.0, player->getPos().y, player->getPos().z);
		if(player->getPos().z > 8.0)
			player->setPos(player->getPos().x, player->getPos().y, 8.0);
		if(player->getPos().z < -8.0)
			player->setPos(player->getPos().x, player->getPos().y, -8.0);
		game.camera->focus = player->getPos();
		game.camera->position = player->getPos() + glm::vec3(8, 6, 6);

		// update player shooting
		if(game.input->isActionPressed("shoot"))
		{
			KinematicBody *newBullet = new KinematicBody();
			newBullet->mesh = loadMesh("../res/meshes/small-sphere.obj");
			newBullet->texture = loadTexture("../res/textures/yellow.jpg");
			newBullet->setPos(shootPoint->getGlobalPos(game.root).x, shootPoint->getGlobalPos(game.root).y, shootPoint->getGlobalPos(game.root).z);
			newBullet->name = "bullet";
			directions.push_back(glm::normalize(shootPoint->getGlobalPos(game.root) - player->getGlobalPos(game.root)));
			distances.push_back(0.0);
			player->addChild(newBullet);
		}

		for(int i = 1; i < player->children.size(); i++)
		{
			player->children[i]->move(directions[i-1] * bulletSpeed);
			distances[i-1] += bulletSpeed;
			if(distances[i-1] > 10.0)
			{
				player->removeChild(player->children[i]);
				distances.erase(distances.begin() + i-1);
				directions.erase(directions.begin() + i-1);
			}
		}

		// instantiate enemies
		// update enemy positions
		game.run();
	}
	return 0;
}
