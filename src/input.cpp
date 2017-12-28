#include "input.h"

Input::Input()
{
	if(SDL_Init(SDL_INIT_GAMECONTROLLER))
	{
		std::cerr<<"Could not initialize SDL for input handling. Error: "<<SDL_GetError()<<std::endl;
		exit(1);
	}
}

Input::~Input()
{
	SDL_Quit();
}

void Input::InsertNewAction(std::string& name, SDL_Keycode key)
{
	inputMap.insert(std::pair<std::string&, SDL_Keycode>(name, key));
	isDown.push_back(false);
	wasDownLastFrame.push_back(false);
}

void Input::Update()
{
	wasDownLastFrame = isDown;
	for(std::map<std::string, SDL_Keycode>::iterator i = inputMap.begin(); i != inputMap.end(); i++)
	{
	}
}

bool Input::IsActionToggled(std::string& action)
{
}

bool Input::IsActionPressed(std::string& action)
{
}
