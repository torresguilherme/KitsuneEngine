#ifndef STATICBODY_HPP_
#define STATICBODY_HPP_
#include "physics.hpp"

class StaticBody: public Node
{
	public:
	CollisionShape* collider;

	enum
	{
		SPHERE_COL,
		BOX_COL
	};

	StaticBody();
	~StaticBody();
	int addCollider(int, CollisionLayer&);
};

#endif
