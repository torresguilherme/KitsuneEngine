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

#include "input.hpp"
using namespace std;

Input::Input()
{
	if(SDL_Init(SDL_INIT_GAMECONTROLLER))
	{
		cerr<<"Could not initialize SDL for input handling. Error: "<<SDL_GetError()<<endl;
		exit(1);
	}
}

Input::~Input()
{
	SDL_Quit();
}

void Input::insertNewAction(string name, SDL_Scancode key)
{
	inputMap.insert(pair<string, SDL_Scancode>(name, key));
	isDown.push_back(false);
	wasDownLastFrame.push_back(false);
}

void Input::update()
{
	wasDownLastFrame = isDown;
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	for(map<string, SDL_Scancode>::iterator i = inputMap.begin(); i != inputMap.end(); i++)
	{
		isDown[distance(inputMap.begin(), i)] = state[(*i).second];
	}
}

bool Input::isActionToggled(string action)
{
	if(!inputMap.empty())
	{
		map<string, SDL_Scancode>::iterator it = inputMap.find(action);
		return isDown[distance(inputMap.begin(), it)] && !wasDownLastFrame[distance(inputMap.begin(), it)];
	}

	else
	{
		return false;
	}
}

bool Input::isActionPressed(string action)
{
	if(!inputMap.empty())
	{
		map<string, SDL_Scancode>::iterator it = inputMap.find(action);
		return isDown[distance(inputMap.begin(), it)];
	}

	else
	{
		return false;
	}
}
