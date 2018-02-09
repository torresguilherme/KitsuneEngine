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

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <ctime>

// errors
#define ERROR_INIT_WINDOW 1
#define ERROR_SET_GL_CONTEXT 2
#define ERROR_INIT_GLEW 3

class Display
{
	private:
	SDL_Window *window;
	SDL_GLContext glContext;

	// frame control
	//double last_frame;
	//double current_frame;
	//double frame_interval;
	//double FPS;

	public:
	bool isClosed;
	//double FPScap;
	//bool isFPScapped;

	Display(unsigned int, unsigned int, const std::string&);
	~Display();
	void run();
	void clear(float, float, float, float);
	void update();
};

#endif
