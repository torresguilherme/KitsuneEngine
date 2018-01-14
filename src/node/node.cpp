#include "node.hpp"
using namespace glm;

Transform::Transform()
{
	translation = vec3(0.0, 0.0, 0.0);
}

Transform::~Transform()
{
}

mat4 Transform::getTransformation()
{
	mat4 transformation(1.0);
	transformation = glm::translate(transformation, this->translation);
	return transformation;
}

Node::Node()
{
}

Node::~Node()
{
}

void Node::update()
{
}
