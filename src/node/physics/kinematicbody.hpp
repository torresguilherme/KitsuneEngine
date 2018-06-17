#ifndef KINEMATICBODY_HPP_
#define KINEMATICBODY_HPP_
#include "staticbody.hpp"

class KinematicBody: public StaticBody
{
	public:
	KinematicBody();
	~KinematicBody();

	void move(glm::vec3);
	void moveAndCollide(glm::vec3);
};

#endif
