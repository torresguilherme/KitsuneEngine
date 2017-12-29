#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <ctime>

// errors
#define ERROR_INIT_WINDOW 1
#define ERROR_SET_GL_CONTEXT 2
#define ERROR_INIT_GLEW 3

class Display
{
	private:
	SDL_Window *window;
	SDL_GLContext glContext;

	// frame control
	//double last_frame;
	//double current_frame;
	//double frame_interval;
	//double FPS;

	public:
	bool isClosed;
	//double FPScap;
	//bool isFPScapped;

	Display(unsigned int, unsigned int, const std::string&);
	~Display();
	void Run();
	void Clear(float, float, float, float);
	void Update();
};

#endif
