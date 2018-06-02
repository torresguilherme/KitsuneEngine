#include "sprite.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../render/stb_image.h"

using namespace std;
using namespace glm;

Sprite::Sprite()
{
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

void Sprite::draw()
{
}

int Sprite::loadTexture(const char *fileName, int mode)
{
	if(mode < REPEAT || mode > CLAMP_TO_BORDER)
	{
		cerr<<"error: invalid texture mode"<<endl;
		return 1;
	}

	unsigned char* imageData = stbi_load(fileName, &width, &height, &numComponents, 4);

	if(imageData == NULL)
	{
		cerr<<"error: image file "<<fileName<<" can't be loaded"<<endl;
		return 1;
	}

	// gererate texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture to the intended mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);

	// image filters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// now we send the image to the GPU and done
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	// free memory
	stbi_image_free(imageData);
	
	return 0;
}
