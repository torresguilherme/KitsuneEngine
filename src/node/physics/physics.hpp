#ifndef PHYSICS_HPP_
#define PHYSICS_HPP_
#include "../node.hpp"

class CollisionShape
{
	public:
	Transform transform;
	Node *parent;
};

class CollisionSphere: public CollisionShape
{
	public:
	float radius;

	CollisionSphere(float rad)
	{
		radius = rad;
	}
};

class CollisionBox: public CollisionShape
{
	public:
	float xLength;
	float yLength;
	float zLength;

	CollisionBox(float x, float y, float z)
	{
		xLength = x;
		yLength = y;
		zLength = z;
	}
};

#endif
