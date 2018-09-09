#include "kinematicbody.hpp"
using namespace glm;
using namespace std;

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

int KinematicBody::attachScript(string fileName)
{
	int ret = StaticBody::attachScript(fileName);
	return ret;
}

void KinematicBody::moveAndCollide(vec3 dir)
{
}
