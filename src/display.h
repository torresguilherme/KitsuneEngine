#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <string>

// errors
#define ERROR_INIT_WINDOW 1
#define ERROR_SET_GL_CONTEXT 2
#define ERROR_INIT_GLEW 3

class Display
{
	private:
	SDL_Window *window;
	SDL_GLContext glContext;

	public:
	bool isClosed;

	Display(unsigned int, unsigned int, const std::string&);
	~Display();
	void Clear(float, float, float, float);
	void Update();
};
