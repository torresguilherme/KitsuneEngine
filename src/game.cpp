#include "game.hpp"

Game::Game()
{
	screen = new Display(800, 600, "test");
	input = new Input;
	isFPScapped = true;
	FPS = 144.0;
	frameInterval = 1/FPS;
	lastFrame = clock();
	nodeNum = 1;
	nodes.emplace_back();
	nodes[0].mesh = loadMesh("../res/meshes/cube.obj");
}

Game::~Game()
{
	nodes.clear();
	delete screen;
	delete input;
}

void Game::run()
{
	while(!screen->isClosed)
	{
		screen->clear(0.0f, 0.0f, 0.0f, 1.0f);
		input->update();
		for(int i = 0; i < nodeNum; i++)
		{
			nodes[i].update();
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
		std::cout<<curFPS<<std::endl;
	}
}

void Game::quit()
{
	screen->isClosed = true;
}
