#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "node2d.hpp"

class Sprite: public Node2D
{
	GLuint texture;
	public:
	int width, height, numComponents;

	enum
	{
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	Sprite();
	virtual ~Sprite();
	virtual void update(double);
	virtual void draw();

	int loadTexture(const char *fileName, int mode);
};

#endif
