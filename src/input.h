#ifndef INPUT_H_
#define INPUT_H_
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

class Input
{
	std::vector<bool> isDown;
	std::vector<bool> wasDownLastFrame;
	std::map<std::string, SDL_Keycode> inputMap;

	public:
	Input();
	~Input();
	void Update();
	void InsertNewAction(std::string&, SDL_Keycode);
	bool IsActionToggled(std::string&);
	bool IsActionPressed(std::string&);
};

#endif
