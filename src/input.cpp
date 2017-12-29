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

void Input::InsertNewAction(string name, SDL_Scancode key)
{
	inputMap.insert(pair<string, SDL_Scancode>(name, key));
	isDown.push_back(false);
	wasDownLastFrame.push_back(false);
}

void Input::Update()
{
	wasDownLastFrame = isDown;
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	for(map<string, SDL_Scancode>::iterator i = inputMap.begin(); i != inputMap.end(); i++)
	{
		isDown[distance(inputMap.begin(), i)] = state[(*i).second];
	}
}

bool Input::IsActionToggled(string action)
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

bool Input::IsActionPressed(string action)
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
