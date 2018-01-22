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
	mat4 m_transformation(1.0);
	m_transformation = glm::translate(m_transformation, this->translation);

	mat4 m_rotationX = glm::rotate(rotation.x, vec3(1.0, 0.0, 0.0));
	mat4 m_rotationY = glm::rotate(rotation.y, vec3(0.0, 1.0, 0.0));
	mat4 m_rotationZ = glm::rotate(rotation.z, vec3(0.0, 0.0, 1.0));
	mat4 m_rotation = m_rotationZ * m_rotationY * m_rotationX;

	mat4 m_scale(1.0);
	m_scale = glm::scale(m_scale, this->scale);

	return m_transformation * m_rotation * m_scale;
}

Node::Node()
{
	pauseMode = INHERIT;

	Vertex vertices [] =
	{
		Vertex(vec3(-1.0, -1.0, 0.0), vec2(0.0, 0.0)),
		Vertex(vec3(0.0, 1.0, 0.0), vec2(0.0, 0.0)),
		Vertex(vec3(1.0, -1.0, 0.0), vec2(0.0, 0.0)),
		Vertex(vec3(0.0, -1.0, 1.0), vec2(0.0, 0.0))
	};

	vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices);
	shader = new Shader("", "");
	shader->addUniform("transform");

	// transform test
	count = 0.0;
	setScale(0.5, 0.5, 0.5);
}

Node::~Node()
{
	delete mesh;
	delete shader;
}

void Node::update()
{
	//transform test
	//setPos(sinf(count), 0.0, 0.0);
	setRot(cosf(count) * 1, cosf(count) * 1, cosf(count) * 1);
	count += 0.1;

	shader->bind();
	shader->setUniformMat4("transform", transform.getTransformation());
	mesh->draw();
}

vec3 Node::getPos()
{
	return transform.translation;
}

void Node::setPos(float x, float y, float z)
{
	transform.translation = vec3(x, y, z);
}

vec3 Node::getRot()
{
	return transform.rotation;
}

void Node::setRot(float x, float y, float z)
{
	transform.rotation = vec3(x, y, z);
}

vec3 Node::getScale()
{
	return transform.scale;
}

void Node::setScale(float x, float y, float z)
{
	transform.scale = vec3(x, y, z);
}

inline double deg2rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

inline double rad2deg(double radians)
{
	return radians * (180.0 / M_PI);
}

Mesh *loadMesh(string fileName)
{
	ifstream file;
	file.open(fileName.c_str());

	string output;
	string line;

	if(!file.is_open())
	{
		cerr<<"error: could not find mesh file to import: "<<fileName<<endl;
		exit(1);
	}

	// import obj
	Mesh *ret;
	string ext = fileName.substr(fileName.find_last_of(".") + 1);
	if(ext == "obj")
	{
	}

	return ret;
}
