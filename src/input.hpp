#ifndef INPUT_HPP_
#define INPUT_HPP_
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

class Input
{
	std::vector<bool> isDown;
	std::vector<bool> wasDownLastFrame;
	std::map<std::string, SDL_Scancode> inputMap;
	const Uint8 *state;

	public:
	Input();
	~Input();
	void Update();
	void InsertNewAction(std::string, SDL_Scancode);
	bool IsActionToggled(std::string);
	bool IsActionPressed(std::string);
};

#endif
