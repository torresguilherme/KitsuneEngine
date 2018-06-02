#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <iostream>
#include <cassert>

class Texture
{
	public:
	GLuint texture;
	int width, height, numComponents;

	Texture(const std::string);
	~Texture();

	void bind(unsigned int);
};

#endif
