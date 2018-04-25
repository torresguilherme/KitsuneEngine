#ifndef RECT2D_HPP_
#define RECT2D_HPP_

#include "node2d.hpp"

class Rect2D: public Node2D
{
	int width;
	int height;
	glm::vec4 color;

	public:
	Rect2D(int, int, int, int, int, int);
	virtual void update(double);
	virtual void draw();
};
#endif
