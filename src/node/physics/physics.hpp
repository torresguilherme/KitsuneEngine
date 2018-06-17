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

class CollisionLayer
{
	public:
	std::vector<CollisionShape*> colliders;

	void addNew(CollisionShape* newShape)
	{
		colliders.push_back(newShape);
	}

	int remove(CollisionShape* tbr)
	{
		for(unsigned int i = 0; i < colliders.size(); i++)
		{
			if(colliders[i] = tbr)
			{
				colliders.erase(colliders.begin()+i);
				return 0;
			}
		}
	
		std::cout<<"Collider shape to be removed not found"<<std::endl;
		return 1;
	}
	void clear()
	{
		colliders.clear();
	}
};

#endif
