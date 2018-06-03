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

#include "display.hpp"

Display::Display(unsigned int width, unsigned int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if(window == NULL)
	{
		std::cerr<<"Error: could not open window!"<<std::endl;
		exit(ERROR_INIT_WINDOW);
	}

	glContext = SDL_GL_CreateContext(window);

	if(SDL_GL_MakeCurrent(window, glContext))
	{
		std::cerr<<"Error: could not set GL context"<<std::endl;
		exit(ERROR_SET_GL_CONTEXT);
	}

	glewExperimental = true;
	if(glewInit())
	{
		std::cerr<<"Error: failed to initialize GLEW!"<<std::endl;
		exit(ERROR_INIT_GLEW);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// to do: depth clamp

	glEnable(GL_FRAMEBUFFER_SRGB);
	isClosed = false;
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::run()
{
	// to do: get fps, set cap
	while(!isClosed)
	{
		clear(0.5f, 0.5f, 0.0f, 1.0f);
		update();
	}
}

void Display::clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update()
{
	SDL_GL_SwapWindow(window);
	SDL_Event ev;
	while(SDL_PollEvent(&ev))
	{
		if(ev.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}
