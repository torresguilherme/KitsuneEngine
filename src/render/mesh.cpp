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

#include "mesh.hpp"
using namespace glm;
using namespace std;

Vertex::Vertex(const vec3 pos, const vec2 texCoord)
{
	this->pos = pos;
	this->texCoord = texCoord;
}

Mesh::Mesh(vector<vec3> positions, vector<int> vertexIndices,  vector<vec2> texCoords, vector<int> uvIndices, vector<vec3> normals, vector<int> normalIndices)
{
	drawCount = vertexIndices.size();
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	// store vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// store vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(int), &vertexIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

	// store texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//store uv indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[UV_INDEX_B]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, uvIndices.size() * sizeof(uvIndices[0]), &uvIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

	// store normals
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMALS_B]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// store normal indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_INDEX_B]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, normalIndices.size() * sizeof(normalIndices[0]), &normalIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
