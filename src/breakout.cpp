#include "breakout.hpp"

void initGame(Game &game)
{
	// init player
	Rect2D *player = new Rect2D(0.25, 0.1, 1.0, 0.0, 0.0, 1.0);
	player->setPos(0.0, -0.8);
	game.root2d->addChild(player);

	// init ball
	Rect2D *ball = new Rect2D(0.05, 0.05, 0.0, 1.0, 0.0, 1.0);
	game.root2d->addChild(ball);

	// init bricks
	Node2D *bricksFather = new Node2D;
	game.root2d->addChild(bricksFather);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			Rect2D *newBrick = new Rect2D(0.19, 0.09, 0.0, 1.0, 1.0, 1.0);
			newBrick->setPos(-0.9 + (0.2 * j), 0.95 - (0.1 * i));
			bricksFather->addChild(newBrick);
		}
	}

	// init inputs
	game.input->insertNewAction("reset", SDL_SCANCODE_R);
	game.input->insertNewAction("quit", SDL_SCANCODE_Q);
	game.input->insertNewAction("pauseUnpause", SDL_SCANCODE_LEFT);
	game.input->insertNewAction("info", SDL_SCANCODE_RIGHT);
}

void gameLoop(Game &game)
{
	while(!game.screen->isClosed)
	{
		bool paused = false;
		// update player input
		if (game.input->isActionToggled("quit"))
		{
			game.screen->isClosed = true;
		}

		if (game.input->isActionToggled("reset"))
		{
			game.root2d->freeChildren();
			initGame(game);
			std::cout<<"jogo resetado"<<std::endl;
		}

		if (game.input->isActionToggled("pauseUnpause"))
		{
			paused = !paused;
		}

		if (game.input->isActionToggled("info"))
		{
			// to do: print attributes
			paused = true;
			gameCycle(game);
		}

		if(!paused)
		{
			gameCycle(game);
		}
		game.run();
	}
}

void gameCycle(Game &game)
{
	//to do: update player position and movement
	
	int playerSpeed;
	game.input->getMousePos(&playerSpeed, NULL);
	float actualPlayerSpeed = (float)(playerSpeed - 400) / 2000;
	game.root2d->children[0]->transform.position.x += actualPlayerSpeed;

	//to do: update ball position w collisions
}
