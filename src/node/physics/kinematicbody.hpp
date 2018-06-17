#ifndef KINEMATICBODY_HPP_
#define KINEMATICBODY_HPP_
#include "staticbody.hpp"

class KinematicBody: public StaticBody
{
	public:
	KinematicBody();
	~KinematicBody();

	void moveAndCollide(glm::vec3);
};

#endif
