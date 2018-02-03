#include "game.hpp"

Game::Game(int width, int height, std::string title, int mode)
{
	screen = new Display(width, height, title);

	gameMode = mode;
	if(gameMode == KITSUNE_2D)
	{
		root2d = new Node2D;
	}
	else if(gameMode == KITSUNE_3D)
	{
		root = new Node;
		root->mesh = loadMesh("../res/meshes/monkey.obj");
	}
	else
	{
		std::cerr<<"error: game mode parameter is not valid!"<<std::endl;
		exit(1);
	}

	input = new Input;
	isFPScapped = true;
	FPS = 144.0;
	frameInterval = 1/FPS;
	lastFrame = clock();
}

Game::~Game()
{
	delete screen;
	delete input;
	if(gameMode == KITSUNE_3D)
	{
		delete root;
	}
	else
	{
		delete root2d;
	}
}

void Game::run()
{
	while(!screen->isClosed)
	{
		screen->clear(0.0f, 0.0f, 0.0f, 1.0f);
		input->update();
		if(gameMode == KITSUNE_3D)
		{
			root->update(delta);
		}
		else
		{
			root2d->update(delta);
		}

		curFrame = clock();
		if(isFPScapped)
		{
			curFrameInterval = ((double) curFrame - lastFrame)/CLOCKS_PER_SEC;
			while(curFrameInterval <= frameInterval)
			{
				curFrame = clock();
				curFrameInterval = ((double) curFrame - lastFrame)/CLOCKS_PER_SEC;
			}

			curFPS = 1/curFrameInterval;
			delta = curFrameInterval;
		}

		else
		{
			curFPS = 1/(((double) curFrame - lastFrame)/CLOCKS_PER_SEC);
			delta = 1/curFPS;
		}

		screen->update();
		lastFrame = curFrame;
		std::cout<<curFPS<<" FPS"<<std::endl;
	}
}

void Game::quit()
{
	screen->isClosed = true;
}
