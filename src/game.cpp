#include "game.hpp"

Game::Game()
{
	screen = new Display(800, 600, "test");
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
}

void Game::run()
{
	while(!screen->isClosed)
	{
		input->update();

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

		screen->clear(0.5f, 0.0f, 0.5f, 1.0f);
		screen->update();
		lastFrame = curFrame;
		std::cout<<curFPS<<std::endl;
	}
}

void Game::quit()
{
	screen->isClosed = true;
}

static inline void fullDelete(void *ptr)
{
	free(ptr);
	ptr = 0;
}
