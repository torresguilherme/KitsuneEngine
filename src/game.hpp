#ifndef GAME_HPP_
#define GAME_HPP_
#include "display.hpp"
#include "input.hpp"
#include "node/node.hpp"
#include "node2d/node2d.hpp"
#include <vector>
#include <iterator>

#define KITSUNE_2D 0
#define KITSUNE_3D 1

class Game
{
	// game components
	Display* screen;

	// FPS handling
	clock_t lastFrame;
	clock_t curFrame;
	double curFrameInterval;
	double frameInterval;
	double FPS;
	double curFPS;

	// node handling
	int gameMode;
	int currentScene;

	public:
	Node* root;
	Node2D* root2d;
	Input* input;
	bool isFPScapped;
	double delta;

	Game(int, int, std::string, int);
	~Game();
	void run();
	void quit();
};

#endif
