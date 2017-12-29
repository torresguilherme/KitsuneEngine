#ifndef GAME_H_
#define GAME_H_
#include "display.h"
#include "input.h"
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
	void Run();
	void Quit();
};

static inline void fullDelete(void*);

#endif
