#ifndef MATHOBJECTS_HPP_
#define MATHOBJECTS_HPP_

#include <cmath>

class Vector2
{
	glm::vec2 vector;

	public:
	Vector2();
	float x();
	float y();
	void setX();
	void setY();
	//operadores de vetor
	void rotate(float);
};

#endif
