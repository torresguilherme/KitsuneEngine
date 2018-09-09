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

#ifndef NODE2D_HPP_
#define NODE2D_HPP_
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <iterator>
#include <cmath>
#include "../render/mesh.hpp"
#include "../render/shader.hpp"

class Transform2D
{
	public:
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

	Transform2D();
	glm::mat4 getTransformation();
};

class Node2D
{
	public:
	std::string name;
	Transform2D transform;
	std::vector<Node2D*> children;

	enum
	{
		INHERIT,
		STOP,
		PROCESS
	};
	int pauseMode;

	Node2D();
	virtual ~Node2D();
	virtual void update(double);
	virtual void draw();
	void addChild(Node2D*);
	Node2D* getNode(std::string);
	void removeChild(Node2D*);
	void freeChildren();

	void setPos(float, float);
	void rotate(float);
	void setScale(float, float);

	glm::mat4 getTransformation();
};

inline double deg2rad(double);
inline double rad2deg(double);

#endif
