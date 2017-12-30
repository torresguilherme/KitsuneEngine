#ifndef MATH_HPP_
#define MATH_HPP_
#include <cmath>

class Vec2
{
	public:
	float x;
	float y;

	Vec2(float, float);
	float lenght();
	Vec2 normalize();
	float distanceTo(Vec2&);
	Vec2 rotate(float);
};

// operadores: equal, soma, sub, mul por escalar,
// cross prod, dot prod, div por escalar

class Vec3
{
	public:
	float x;
	float y;
	float z;

	Vec3(float, float, float);
	float lenght();
	Vec3 normalize();
	float distanceTo(Vec3&);
	Vec3 rotate(float);
};

// operadores: equal, soma, sub, mul por escalar
// cross prod, dot prod, div por escalar

typedef float Mat4[4][4];
void makeIdentity(Mat4);

// operadores: mul p/ mat4

class Quaternion
{
	public:
	float x;
	float y;
	float z;
	float w;

	Quaternion(float, float, float, float);
	float lenght();
	Quaternion normalize();
	Quaternion conjugate();
};

// operadores: mul p/ quaternion, mul p/ vector3

#endif
