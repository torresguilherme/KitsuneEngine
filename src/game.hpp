#ifndef GAME_HPP_
#define GAME_HPP_
#include "display.hpp"
#include "input.hpp"
#include <SDL2/SDL.h>

class Game
{
	Display* screen;
	Input* input;
	clock_t lastFrame;
	clock_t curFrame;
	double curFrameInterval;
	double frameInterval;
	double FPS;

	public:
	bool isFPScapped;
	double curFPS;
	double delta;

	Game();
	~Game();
	void run();
	void quit();
};

static inline void fullDelete(void*);

#endif
