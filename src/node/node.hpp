#ifndef NODE_HPP_
#define NODE_HPP_
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "../render/mesh.hpp"
#include "../render/shader.hpp"

class Transform
{
	public:
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();
	~Transform();
	glm::mat4 getTransformation();
};

class Node
{
	Transform transform;
	Mesh *mesh;
	Shader *shader;

	public:
	// pause mode
	enum
	{
		INHERIT,
		STOP,
		PROCESS
	};
	int pauseMode;

	Node();
	virtual ~Node();
	virtual void update();

	glm::vec3 getPos();
	void setPos(float, float, float);
	glm::vec3 getRot();
	void setRot(float, float, float);
	glm::vec3 getScale();
	void setScale(float, float, float);

	// testing
	float count;
};

inline double deg2rad(double);
inline double rad2deg(double);

#endif
