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

#include "node2d.hpp"
using namespace std;
using namespace glm;

Transform2D::Transform2D()
{
	position = vec3(0.0, 0.0, 0.0);
	rotation = 0.0f;
	scale = vec3(1.0, 1.0, 1.0);
}

mat4 Transform2D::getTransformation()
{
	mat4 m_transformation(1.0);
	m_transformation = glm::translate(m_transformation, this->position);
	mat4 m_rotation = glm::rotate(rotation, vec3(0.0, 0.0, 1.0));
	mat4 m_scale(1.0);
	m_scale = glm::scale(m_scale, this->scale);

	return m_transformation * m_rotation * m_scale;
}

Node2D::Node2D()
{
	pauseMode = INHERIT;
}

Node2D::~Node2D()
{
}

void Node2D::update(double delta)
{
}

void Node2D::draw()
{
}

void Node2D::setPos(float x, float y)
{
	transform.position = vec3(x, y, 0.0);
}

void Node2D::rotate(float degrees)
{
	transform.rotation = deg2rad((double)degrees);
}

void Node2D::setScale(float x, float y)
{
	transform.scale = vec3(x, y, 0.0);
}

mat4 Node2D::getTransformation()
{
	return transform.getTransformation();
}

inline double deg2rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

inline double rad2deg(double radians)
{
	return radians * (180.0 / M_PI);
}

