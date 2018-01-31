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
	setRot(0.0, count, 0.0);
	count += 0.01;

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

	string line;
	vector<Vertex> vertices;
	vector<int> faceIndexes;
	float data[4];

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
		while(file.good())
		{
			getline(file, line);
			if(line[0] == 'v')
			{
				if(line[1] == 'p')
				{
				}

				else if(line[1] == 't')
				{
				}

				else if(line[1] == 'n')
				{
				}

				else
				{
					string aux = line.substr(line.find_first_of(" ") + 1);
					stringstream ss(aux);
					for(int i = 0; i < 3; i++)
					{
						ss >> data[i];
						cout<<data[i]<<' ';
					}
					vertices.push_back(Vertex(vec3(data[0], data[1], data[2]), vec2(0.0, 0.0)));
					cout<<endl;
				}
			}

			else if(line[0] == 'f')
			{
				string aux = line.substr(line.find_first_of(" ") + 1);
				stringstream ss(aux);
				for(int i = 0; i < 3; i++)
				{
					ss >> data[i];
					data[i]--;
					cout<<data[i]<<' ';
					faceIndexes.push_back(data[i]);
				}
				cout<<endl;
			}
		}
	}

	else
	{
		cerr<<"error: mesh export format is not supported"<<endl;
		exit(1);
	}

	ret = new Mesh(vertices.data(), vertices.size(), faceIndexes);
	return ret;
}
