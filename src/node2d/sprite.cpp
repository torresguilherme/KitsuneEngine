#include "sprite.hpp"

using namespace std;
using namespace glm;

Sprite::Sprite()
{
	position = vec2(0.0, 0.0);
	rotation = 0.0;
	scale = vec2(0.0, 0.0);

	pauseMode = INHERIT;
}

Sprite::~Sprite()
{
	if(texture)
	{
		glDeleteTextures(1, &texture);
	}
}

void Sprite::update(double delta)
{
}

int Sprite::loadTexture(const char *fileName, int mode)
{
	if(mode < REPEAT || mode > CLAMP_TO_BORDER)
	{
		cerr<<"error: invalid texture mode"<<endl;
		return 1;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	return 0;
}
