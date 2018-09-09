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
	virtual int attachScript(std::string);

	int addCollider(int, CollisionLayer&);
};

#endif
