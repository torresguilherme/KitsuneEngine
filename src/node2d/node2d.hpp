#ifndef NODE2D_HPP_
#define NODE2D_HPP_
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Node2D
{
	public:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	enum
	{
		INHERIT,
		STOP,
		PROCESS
	};
	int pauseMode;

	Node2D();
	virtual ~Node2D();
	virtual void update(double);

	void setPos(float, float);
	void rotate(float);
	void setScale(float, float);
};

class Sprite: public Node2D
{
	SDL_Surface *texture;

	public:
	Sprite();
	virtual ~Sprite();
	virtual void update(double);
};

inline double deg2rad(double);
inline double rad2deg(double);
SDL_Surface *loadTexture(std::string);

#endif
