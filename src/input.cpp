#include "input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::InsertNewAction(std::string& name, SDL_Keycode key)
{
	inputMap.insert(std::pair<std::string&, SDL_Keycode>(name, key));
}

void Input::Update()
{
}

bool Input::IsActionToggled(std::string& action)
{
}

bool Input::IsActionPressed(std::string& action)
{
}
