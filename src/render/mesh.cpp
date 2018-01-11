#include "mesh.hpp"
using namespace glm;
using namespace std;

Vertex::Vertex(const vec3 pos, const vec2 texCoord)
{
	this->pos = pos;
	this->texCoord = texCoord;
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	vector<vec3> positions;
	//vector<vec2> texCoords;
	positions.reserve(numVertices);
	//texCoords.reserve(numVertices);

	for(unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
		//texCoords.push_back(vertices[i].texCoord);
	}

	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}
