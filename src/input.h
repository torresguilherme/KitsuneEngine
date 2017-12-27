#ifndef INPUT_H_
#define INPUT_H_
#include <SDL2/SDL.h>
#include <map>
#include <iterator>

class Input
{
	public:
	std::map<std::string, SDL_Keycode> inputMap;

	Input();
	~Input();
	void Update();
	bool IsActionToggled(std::string&);
	bool IsActionPressed(std::string&);
};

#endif
