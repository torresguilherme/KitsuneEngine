/*************************************************************************/
/*                     This file is part of the                          */
/*                      Kitsune Engine Project                           */
/*************************************************************************/
/* Copyright (c) 2017-2018 Guilherme Torres                              */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

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
	shader->addUniform("u_resolution");

	// transform test
	count = 0.0;
	setScale(0.5, 0.5, 0.5);
}

Node::~Node()
{
	delete mesh;
	delete shader;
}

void Node::update(double delta)
{
	//transform test
	//setPos(sinf(count), 0.0, 0.0);
	setRot(0.0, count, 0.0);
	count += delta;

	shader->bind();
	shader->setUniformMat4("transform", transform.getTransformation());
	shader->setUniformVec2("u_resolution", vec2(640.0, 480.0));
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

Mesh *loadMesh(string sFileName)
{
	const char *fileName = sFileName.c_str();
	FILE* file;
	file = fopen(fileName, "r");

	char line[256];
	vector<vec3> vertices;
	vector<int> faceIndices;
	vector<vec2> texCoords;
	vector<vec3> normals;
	float data[4];
	int intData[4];

	if(!file)
	{
		cerr<<"error: could not find mesh file to import: "<<fileName<<endl;
		exit(1);
	}

	// import obj
	Mesh *ret;
	const char *ext = &fileName[0];
	int i = strlen(fileName);

	while(*ext != '\0')
	{
		ext++;
	}

	while(*ext != '.')
	{
		if(i <= 0)
		{
			cerr<<"error: mesh file does not have an extention"<<endl;
			exit(1);
		}

		ext--;
		i--;
	}

	if(!strcmp(ext, ".obj"))
	{
		while(fscanf(file, "%s", line) != EOF)
		{
			if(!strcmp(line, "v"))
			{
				fscanf(file, "%f %f %f\n", &data[0], &data[1], &data[2]);
				vertices.push_back(vec3(data[0], data[1], data[2]));
			}

			else if(!strcmp(line, "vt"))
			{
				fscanf(file, "%f %f\n", &data[0], &data[1]);
				texCoords.push_back(vec2(data[0], data[1]));
			}

			else if(!strcmp(line, "vn"))
			{
				fscanf(file, "%f %f %f\n", &data[0], &data[1], &data[2]);
				normals.push_back(vec3(data[0], data[1], data[2]));
			}

			else if(!strcmp(line, "f"))
			{
				fscanf(file, "%i %i %i\n", &intData[0], &intData[1], &intData[2]);
				for(int i = 0; i < 3; i++)
				{
					faceIndices.push_back(intData[i] - 1);
				}
			}
		}
	}

	else
	{
		cerr<<"error: mesh export format is not supported"<<endl;
		exit(1);
	}

	ret = new Mesh(vertices, faceIndices, texCoords, normals);
	return ret;
}
