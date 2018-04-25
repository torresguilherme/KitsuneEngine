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

#ifndef NODE_HPP_
#define NODE_HPP_
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <cstdlib>
#include <cstring>
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
	public:
	Transform transform;
	Mesh *mesh;
	Shader *shader;

	// pause mode
	enum
	{
		INHERIT,
		STOP,
		PROCESS
	};
	int pauseMode;

	Node();
	virtual ~Node();
	virtual void update(double);
	virtual void draw(glm::mat4, glm::mat4);

	glm::vec3 getPos();
	void setPos(float, float, float);
	glm::vec3 getRot();
	void setRot(float, float, float);
	glm::vec3 getScale();
	void setScale(float, float, float);

	// testing
	float count;
};

inline double deg2rad(double);
inline double rad2deg(double);
Mesh *loadMesh(std::string);

#endif
