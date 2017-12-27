#include "display.h"

Display::Display(unsigned int width, unsigned int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if(window == NULL)
	{
		std::cerr<<"Error: could not open window!"<<std::endl;
		exit(ERROR_INIT_WINDOW);
	}

	glContext = SDL_GL_CreateContext(window);

	if(SDL_GL_MakeCurrent(window, glContext))
	{
		std::cerr<<"Error: could not set GL context"<<std::endl;
		exit(ERROR_SET_GL_CONTEXT);
	}

	glewExperimental = true;
	if(glewInit())
	{
		std::cerr<<"Error: failed to initialize GLEW!"<<std::endl;
		exit(ERROR_INIT_GLEW);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	isClosed = false;

	//FPS cap
	//isFPScapped = true;
	//FPScap = 60.0;
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::Run()
{
	// to do: get fps, set cap
	while(!isClosed)
	{
		Clear(0.5f, 0.5f, 0.0f, 1.0f);
		Update();
	}
}

void Display::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update()
{
	SDL_GL_SwapWindow(window);
	SDL_Event ev;
	while(SDL_PollEvent(&ev))
	{
		if(ev.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}
