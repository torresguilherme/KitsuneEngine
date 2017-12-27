#include "game.h"

Game::Game()
{
	screen = new Display(800, 600, "test");
	isFPScapped = true;
	FPS = 144.0;
	frameInterval = 1/FPS;
	lastFrame = clock();
}

Game::~Game()
{
	fullDelete(screen);
}

void Game::Run()
{
	while(!screen->isClosed)
	{
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

		lastFrame = curFrame;
		std::cout<<curFPS<<std::endl;
		screen->Clear(0.5f, 0.0f, 0.5f, 1.0f);
		screen->Update();
	}
}
