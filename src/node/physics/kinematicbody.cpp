#include "kinematicbody.hpp"
using namespace glm;

KinematicBody::KinematicBody()
{
}

KinematicBody::~KinematicBody()
{
	if(collider)
	{
		delete collider;
	}
}

void KinematicBody::moveAndCollide(vec3 dir)
{
}
