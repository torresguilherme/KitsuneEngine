#include "rect2d.hpp"

Rect2D::Rect2D(int width, int height, int red, int blue, int green, int alpha)
{
	this->width = width;
	this->height = height;
	this->color = glm::vec4(red, blue, green, alpha);
}

void Rect2D::update(double delta)
{
}

void Rect2D::draw()
{
}
