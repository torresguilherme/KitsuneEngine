#include "input.h"
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
	state = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
	for(map<string, SDL_Scancode>::iterator i = inputMap.begin(); i != inputMap.end(); i++)
	{
		isDown[distance(inputMap.begin(), i)] = state[(*i).second];
	}
	//delete state;
}

bool Input::IsActionToggled(string action)
{
	map<string, SDL_Scancode>::iterator it = inputMap.find(action);
	return isDown[distance(inputMap.begin(), it)] && !wasDownLastFrame[distance(inputMap.begin(), it)];
}

bool Input::IsActionPressed(string action)
{
	map<string, SDL_Scancode>::iterator it = inputMap.find(action);
	cout<<isDown[distance(inputMap.begin(), it)]<<' '<<distance(inputMap.begin(), it)<<endl;
	return isDown[distance(inputMap.begin(), it)];
}
