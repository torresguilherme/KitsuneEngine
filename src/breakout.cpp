#include "breakout.hpp"

void initGame(Game &game, CollisionLayer &c)
{
	// init player
	Rect2D *player = new Rect2D(0.2, 0.1, 1.0, 0.0, 0.0, 1.0);
	player->setPos(0.0, -0.8);
	player->name = "player";
	c.colliders.push_back(player);
	game.root2d->addChild(player);

	// init ball
	Rect2D *ball = new Rect2D(0.05, 0.05, 0.0, 1.0, 0.0, 1.0);
	game.root2d->addChild(ball);
	c.colliders.push_back(ball);
	ball->name = "ball";

	// init bricks
	Node2D *bricksFather = new Node2D;
	game.root2d->addChild(bricksFather);
	bricksFather->name = "bricksFather";
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			Rect2D *newBrick = new Rect2D(0.19, 0.09, 0.0, 1.0, 1.0, 1.0);
			newBrick->setPos(-0.9 + (0.2 * j), 0.95 - (0.1 * i));
			newBrick->name = "brick";
			c.colliders.push_back(newBrick);
			bricksFather->addChild(newBrick);
		}
	}

	// init inputs
	game.input->insertNewAction("reset", SDL_SCANCODE_R);
	game.input->insertNewAction("quit", SDL_SCANCODE_Q);
	game.input->insertNewAction("pauseUnpause", SDL_SCANCODE_LEFT);
	game.input->insertNewAction("info", SDL_SCANCODE_RIGHT);
}

void gameLoop(Game &game, CollisionLayer &c)
{
	bool paused = true;
	float ballDirectionX = 0.01;
	float ballDirectionY = 0.005;
	while(!game.screen->isClosed)
	{
		// update player input
		if (game.input->isActionToggled("quit"))
		{
			game.screen->isClosed = true;
		}

		if (game.input->isActionToggled("reset"))
		{
			game.root2d->freeChildren();
			c.colliders.clear();
			ballDirectionX = 0.01;
			ballDirectionY = 0.005;
			initGame(game, c);
			std::cout<<"jogo resetado"<<std::endl;
		}

		if (game.input->isActionToggled("pauseUnpause"))
		{
			paused = !paused;
		}

		if (game.input->isActionToggled("info"))
		{
			paused = true;
			gameCycle(game, true, c, ballDirectionX, ballDirectionY);
		}

		if(!paused)
		{
			gameCycle(game, false, c, ballDirectionX, ballDirectionY);
		}
		game.run();
	}
}

void gameCycle(Game &game, bool debug, CollisionLayer &c, float &ballDirX, float &ballDirY)
{
	// to do: difficulty levels
	// to do: undestructible bricks
	// to do: ost?
	// player position and movement
	int playerSpeed;
	game.input->getMousePos(&playerSpeed, NULL);
	float actualPlayerSpeed = (float)(playerSpeed - 400) / 2000;
	game.root2d->getNode("player")->transform.position.x += actualPlayerSpeed;
	if(game.root2d->getNode("player")->transform.position.x <= -1.0)
	{
		game.root2d->getNode("player")->transform.position.x = -1.0;
	}
	else if(game.root2d->getNode("player")->transform.position.x >= 1.0)
	{
		game.root2d->getNode("player")->transform.position.x = 1.0;
	}

	if(debug)
	{
		std::cout<<"Posicao do jogador: x = "<<game.root2d->getNode("player")->transform.position.x<<std::endl;
		std::cout<<"Velocidade do jogador no eixo X: "<<actualPlayerSpeed<<std::endl;
	}

	// update ball position w collisions
	Node2D *ball = game.root2d->getNode("ball");
	ball->transform.position.x += ballDirX;
	for (unsigned int i = 0; i < c.colliders.size(); i++)
	{
		if(c.colliders[i] != NULL
		&& abs(ball->transform.position.x - c.colliders[i]->transform.position.x) < 0.1
		&& abs(ball->transform.position.y - c.colliders[i]->transform.position.y) < 0.05
		&& ball != c.colliders[i])
		{
			ballDirX = -ballDirX;
			if (c.colliders[i]->name == "brick")
			{
				game.root2d->getNode("bricksFather")->removeChild(c.colliders[i]);
				c.colliders.erase(c.colliders.begin()+i);
			}
		}
	}

	ball->transform.position.y += ballDirY;
	for (unsigned int i = 0; i < c.colliders.size(); i++)
	{
		if(c.colliders[i] != NULL
		&& abs(ball->transform.position.y - c.colliders[i]->transform.position.y) < 0.05
		&& abs(ball->transform.position.x - c.colliders[i]->transform.position.x) < 0.1
		&& ball != c.colliders[i])
		{
			ballDirY = -ballDirY;
			if (c.colliders[i]->name == "brick")
			{
				game.root2d->getNode("bricksFather")->removeChild(c.colliders[i]);
				c.colliders.erase(c.colliders.begin()+i);
			}

			else if(c.colliders[i]->name == "player")
			{
				ballDirX -= actualPlayerSpeed;
				ballDirY += abs(actualPlayerSpeed);
			}
		}
	}

	// check collision with borders
	if(ball->transform.position.x > 1.0 || ball->transform.position.x < -1.0)
	{
		ballDirX = -ballDirX;
	}

	if(ball->transform.position.y > 1.0)
	{
		ballDirY = -ballDirY;
	}

	// use max speed
	if (ballDirX > 0.1)
		ballDirX = 0.1;
	if (ballDirY > 0.1)
		ballDirY = 0.1;

	if (ballDirX < -0.1)
		ballDirX = -0.1;
	if (ballDirY < -0.1)
		ballDirY = -0.1;

	if(debug)
	{
		std::cout<<"Posicao da bola: x = "<<ball->transform.position.x;
		std::cout<<" y = "<<ball->transform.position.y<<std::endl;
	}
}
