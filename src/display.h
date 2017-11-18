#include "kitsune-commons.h"

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
