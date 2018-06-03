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

#ifndef MESH_HPP_
#define MESH_HPP_
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iterator>

class Vertex
{
	// this class is technically useless right now
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
		TEXCOORD_VB,
		UV_INDEX_B,
		NORMALS_B,
		NORMAL_INDEX_B,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint indexBufferObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;

	public:
	Mesh(std::vector<glm::vec3>, std::vector<int>, std::vector<glm::vec2>, std::vector<int>, std::vector<glm::vec3>, std::vector<int>);
	virtual ~Mesh();
	void draw();
};

#endif
