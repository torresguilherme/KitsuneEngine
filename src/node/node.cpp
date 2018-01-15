#include "node.hpp"
using namespace glm;
using namespace std;

Transform::Transform()
{
	translation = vec3(0.0, 0.0, 0.0);
	rotation = vec3(0.0, 0.0, 0.0);
	scale = vec3(1.0, 1.0, 1.0);
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
	Vertex vertices [] =
	{
		Vertex(vec3(-1.0, -1.0, 0.0), vec2(0.0, 0.0)),
		Vertex(vec3(0.0, 1.0, 0.0), vec2(0.0, 0.0)),
		Vertex(vec3(1.0, -1.0, 0.0), vec2(0.0, 0.0))
	};

	mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	shader = new Shader("", "");
	//shader->addUniform("transform");
}

Node::~Node()
{
	delete mesh;
	delete shader;
}

void Node::update()
{
	shader->bind();
	mesh->draw();
}
