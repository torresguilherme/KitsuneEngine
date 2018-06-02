#ifndef RECT2D_HPP_
#define RECT2D_HPP_

#include "node2d.hpp"

class Rect2D: public Node2D
{
	glm::vec4 color;

	Mesh *mesh;
	Shader *shader;

	public:
	int width;
	int height;

	Rect2D(float, float, float, float, float, float);
	~Rect2D();
	virtual void update(double);
	virtual void draw();
};
#endif
