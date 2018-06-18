#include "game.hpp"

using namespace std;
const int S_HEIGHT = 600;
const int S_WIDTH = 1040;

int main()
{
	Game game(S_WIDTH, S_HEIGHT, "KE testing", KITSUNE_3D);
	srand(time(NULL));
	//instantiate player
	KinematicBody *player = new KinematicBody();
	game.root->addChild(player);
	player->mesh = loadMesh("../res/meshes/tank.obj");
	player->texture = loadTexture("../res/textures/camouflage.jpg");
	float playerSpeed = 0.1;
	int playerHp = 5;
	float lastDamage = 0;
	float invincible = 1.0;
	int killCount = 0;
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

	// enemies
	vector<KinematicBody*> enemies;
	vector<glm::vec3> enemyDirections;
	vector<int> enemyHp;
	vector<float> backOff;
	float enemySpeed = 0.03;
	int maxEnemies = 3;
	bool started = false;
	float lastSpawn = 0;
	float spawnCooldown = 0.8;

	// enemy spawn spots
	vector<glm::vec3> spots;
	spots.push_back(glm::vec3(8.0, 1.0, 8.0));
	spots.push_back(glm::vec3(-8.0, 1.0, 8.0));
	spots.push_back(glm::vec3(8.0, 1.0, -8.0));
	spots.push_back(glm::vec3(-8.0, 1.0, -8.0));
	spots.push_back(glm::vec3(8.0, 1.0, 4.0));
	spots.push_back(glm::vec3(4.0, 1.0, 8.0));
	spots.push_back(glm::vec3(-4.0, 1.0, 8.0));
	spots.push_back(glm::vec3(8.0, 1.0, -4.0));
	spots.push_back(glm::vec3(-8.0, 1.0, -4.0));

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
		game.camera->position = player->getPos() + glm::vec3(10, 7, 7);

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
		if(enemies.size() == 0 && started)
		{
			// nova fase com mais dificuldade
			started = false;
			lastSpawn = 0;
			maxEnemies++;
			player->setPos(0.0, 1.0, 0.0);

		}
		else if(enemies.size() < maxEnemies)
		{
			if(lastSpawn <= 0)
			{
				KinematicBody *newEnemy = new KinematicBody();
				newEnemy->mesh = loadMesh("../res/meshes/large-sphere.obj");
				newEnemy->texture = loadTexture("../res/textures/red.jpg");

				int ind = rand() % spots.size();
				game.root->addChild(newEnemy);
				newEnemy->setPos(spots[ind].x, spots[ind].y, spots[ind].z);

				enemyDirections.push_back(player->getPos() - newEnemy->getPos());
				enemyHp.push_back(5);
				enemies.push_back(newEnemy);
				backOff.push_back(0);

				lastSpawn = spawnCooldown;
			}
			else
			{
				lastSpawn -= 0.01;
			}
			started = true;
		}

		// update enemy positions
		bool oneIsBackingOff = false;
		for(int i = 0; i < enemies.size(); i++)
		{
			enemyDirections[i] = glm::normalize(player->getPos() - enemies[i]->getPos());
			enemyDirections[i].y = 0.0;
			for(int j = 0; j < enemies.size(); j++)
			{
				if(!oneIsBackingOff && i != j && glm::distance(enemies[i]->getPos(), enemies[j]->getPos()) < 2.0)
				{
					backOff[i] = 1.0;
					oneIsBackingOff = true;
				}
			}

			if(backOff[i] <= 0.0)
			{
				enemies[i]->move(enemyDirections[i] * enemySpeed);
			}
			else
			{
				enemies[i]->move(-enemyDirections[i] * enemySpeed);
				backOff[i] -= enemySpeed;
			}

			for(int j = 1; j < player->children.size(); j++)
			{
				// update enemy damage
				if(glm::distance(player->children[j]->getPos(), enemies[i]->getPos()) < 1.0)
				{
					player->removeChild(player->children[j]);
					directions.erase(directions.begin() + j-1);
					distances.erase(distances.begin() + j-1);
					enemyHp[i]--;
				}
			}

			if(enemyHp[i] <= 0)
			{
				game.root->removeChild(enemies[i]);
				enemies.erase(enemies.begin() + i);
				enemyDirections.erase(enemyDirections.begin() + i);
				enemyHp.erase(enemyHp.begin() + i);
				killCount++;
			}
			
			// update player damage
			if(glm::distance(player->getPos(), enemies[i]->getPos()) < 1.5)
			{
				if(lastDamage <= 0)
				{
					playerHp--;
					lastDamage = invincible;
				}
			}

			if(lastDamage > 0)
				lastDamage -= 0.01;
		}

		// game over
		if(playerHp <= 0)
		{
			game.screen->isClosed = true;
		}
		game.run();
	}

	std::cout<<"Inimigos abatidos: "<<killCount<<std::endl;
	return 0;
}
