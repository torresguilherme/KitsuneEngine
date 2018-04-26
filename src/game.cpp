/*************************************************************************/
/*                     This file is part of the                          */
/*                      Kitsune Engine Project                           */
/*************************************************************************/
/* Copyright (c) 2017-2018 Guilherme Torres                              */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "game.hpp"

Camera::Camera()
{
	position = glm::vec3(4, 3, 3);
	focus = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, focus, up);
}

Game::Game(int width, int height, std::string title, int mode)
{
	screen = new Display(width, height, title);

	gameMode = mode;
	if(gameMode == KITSUNE_2D)
	{
		// testing rect
		root2d = new Rect2D(0.5, 0.5, 1.0, 1.0, 0.0, 1.0);

	}
	else if(gameMode == KITSUNE_3D)
	{
		root = new Node;
		// testing
		root->mesh = loadMesh("../res/meshes/monkey.obj");
	}
	else
	{
		std::cerr<<"error: game mode parameter is not valid!"<<std::endl;
		exit(1);
	}

	camera = new Camera;
	projectionMat = glm::perspective(glm::radians(45.0f), (float) width / (float) height, near, far);
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
	delete camera;
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
			root->draw(glm::mat4(1.0), projectionMat, camera->getViewMatrix());
		}
		else
		{
			root2d->update(delta);
			root2d->draw();
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
		//std::cout<<delta<<" deltaTime"<<std::endl;
	}
}

void Game::quit()
{
	screen->isClosed = true;
}
