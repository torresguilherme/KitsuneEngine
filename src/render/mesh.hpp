#ifndef MESH_HPP_
#define MESH_HPP_
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iterator>

class Vertex
{
	static const int SIZE = 3;

	public:
	glm::vec3 pos;
	glm::vec2 texCoord;

	Vertex(const glm::vec3 pos, const glm::vec2 texCoord);
};

class Mesh
{
	enum
	{
		POSITION_VB,
		INDEX_VB,
		//TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint indexBufferObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;

	public:
	Mesh(Vertex*, unsigned int, std::vector<int>);
	virtual ~Mesh();
	void draw();
};

#endif
