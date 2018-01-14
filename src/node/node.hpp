#ifndef NODE_HPP_
#define NODE_HPP_
#include <glm/gtc/matrix_transform.hpp>
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

	public:
	Node();
	~Node();
	void update();
};

#endif
