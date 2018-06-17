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

#ifndef GAME_HPP_
#define GAME_HPP_
#include "kitsune.hpp"
#include <vector>
#include <iterator>

#define KITSUNE_2D 0
#define KITSUNE_3D 1

class Camera
{
	public:
	glm::vec3 position;
	glm::vec3 focus;
	glm::vec3 up;

	Camera();
	glm::mat4 getViewMatrix();
};

class Game
{
	// game components
	public:
	Display* screen;
	CollisionLayer layer0;

	// FPS handling
	private:
	clock_t lastFrame;
	clock_t curFrame;
	double curFrameInterval;
	double frameInterval;
	double FPS;
	double curFPS;

	// node handling
	int gameMode;
	int currentScene;

	// camera
	public:
	Camera *camera;
	private:
	glm::mat4 projectionMat;
	const float near = 0.1f;
	const float far = 100.0f;

	public:
	Node* root;
	Node2D* root2d;
	Input* input;
	bool isFPScapped;
	double delta;

	Game(int, int, std::string, int);
	~Game();
	void run();
	void quit();
};

#endif
