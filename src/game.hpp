#ifndef GAME_HPP_
#define GAME_HPP_
#include "display.hpp"
#include "input.hpp"
#include "node/node.hpp"
#include <vector>
#include <iterator>

class Game
{
	// game components
	Display* screen;
	Input* input;

	// FPS handling
	clock_t lastFrame;
	clock_t curFrame;
	double curFrameInterval;
	double frameInterval;
	double FPS;
	double curFPS;

	// node handling
	std::vector<Node> nodes;
	int nodeNum;

	public:
	bool isFPScapped;
	double delta;

	Game();
	~Game();
	void run();
	void quit();
};

#endif
