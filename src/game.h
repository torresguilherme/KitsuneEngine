#ifndef GAME_H_
#define GAME_H_
#include "display.h"

static inline void fullDelete(void *ptr)
{
	free(ptr);
	ptr = 0;
}

class Game
{
	Display* screen;
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
};

#endif
