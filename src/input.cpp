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

void Input::InsertNewAction(std::string name, SDL_Keycode key)
{
	inputMap.insert(std::pair<std::string, SDL_Keycode>(name, key));
	isDown.push_back(false);
	wasDownLastFrame.push_back(false);
}

void Input::Update()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	wasDownLastFrame = isDown;
	for(std::map<std::string, SDL_Keycode>::iterator i = inputMap.begin(); i != inputMap.end(); i++)
	{
		std::cout<<std::distance(inputMap.begin(), i)<<std::endl;
		isDown[std::distance(inputMap.begin(), i)] = state[(*i).second];
	}
	//delete state;
}

bool Input::IsActionToggled(std::string action)
{
	std::map<std::string, SDL_Keycode>::iterator it = inputMap.find(action);
	return isDown[std::distance(inputMap.begin(), it)] && !wasDownLastFrame[std::distance(inputMap.begin(), it)];
}

bool Input::IsActionPressed(std::string action)
{
	std::map<std::string, SDL_Keycode>::iterator it = inputMap.find(action);
	return isDown[std::distance(inputMap.begin(), it)];
}
