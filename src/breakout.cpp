#include "breakout.hpp"

void initGame(Game &game)
{
	// init player
	Rect2D *player = new Rect2D(0.25, 0.1, 1.0, 0.0, 0.0, 1.0);
	player->setPos(0.0, -0.8);
	player->name = "player";
	game.root2d->addChild(player);

	// init ball
	Rect2D *ball = new Rect2D(0.05, 0.05, 0.0, 1.0, 0.0, 1.0);
	game.root2d->addChild(ball);
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
	bool paused = true;
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
			initGame(game);
			std::cout<<"jogo resetado"<<std::endl;
		}

		if (game.input->isActionToggled("pauseUnpause"))
		{
			paused = !paused;
		}

		if (game.input->isActionToggled("info"))
		{
			paused = true;
			gameCycle(game, true);
		}

		if(!paused)
		{
			gameCycle(game, false);
		}
		game.run();
	}
}

void gameCycle(Game &game, bool debug)
{
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
		std::cout<<"Velocidade do jogador no eixo X: "<<actualPlayerSpeed<<std::endl;
	}

	//to do: update ball position w collisions
}
