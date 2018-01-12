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
	//mesh and shader testing
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.10)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(5.0, 0.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(10.0, 10.0))
	};

	Mesh mesh = Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader = Shader("", "");
	//mesh and shader testing

	while(!screen->isClosed)
	{
		screen->clear(0.0f, 0.0f, 0.0f, 1.0f);
		input->update();
		shader.bind();
		mesh.draw();

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
