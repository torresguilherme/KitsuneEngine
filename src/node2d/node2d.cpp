#include "node2d.hpp"
using namespace std;
using namespace glm;

Node2D::Node2D()
{
	position = vec2(0.0, 0.0);
	rotation = 0.0;
	scale = vec2(0.0, 0.0);

	pauseMode = INHERIT;
}

Node2D::~Node2D()
{
}

void Node2D::update(double delta)
{
}

void Node2D::setPos(float x, float y)
{
	position = vec2(x, y);
}

void Node2D::rotate(float degrees)
{
	rotation = deg2rad((double)degrees);
}

void Node2D::setScale(float x, float y)
{
	scale = vec2(x, y);
}

inline double deg2rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

inline double rad2deg(double radians)
{
	return radians * (180.0 / M_PI);
}

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
		delete texture;
	}
}

void Sprite::update(double delta)
{
}
