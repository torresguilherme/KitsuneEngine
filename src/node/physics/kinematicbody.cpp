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

void KinematicBody::move(vec3 dir)
{
	setPos(getPos().x + dir.x, getPos().y + dir.y, getPos().z + dir.z);
}

void KinematicBody::moveAndCollide(vec3 dir)
{
}
