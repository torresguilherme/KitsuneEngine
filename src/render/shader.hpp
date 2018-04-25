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

#ifndef SHADER_HPP_
#define SHADER_HPP_
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <map>

class Shader
{
	enum
	{
		VERT_SHADER,
		FRAG_SHADER,
		//GEOM_SHADER,
		NUM_SHADERS
	};
	GLuint program;
	GLuint shaders[NUM_SHADERS];
	const char* basicVertShader = "../res/shaders/basicShader.vert";
	const char* basicFragShader = "../res/shaders/basicShader.frag";
	const char* basicGeomShader = "../res/shaders/basicShader.geom";
	std::map<std::string, GLuint> uniforms;

	std::string LoadBasicShader(int);

	public:
	Shader(std::string, std::string/*, std::string*/);
	~Shader();
	void bind();
	void update();
	void addUniform(std::string);
	void setUniformi(std::string, int);
	void setUniformf(std::string, float);
	void setUniformVec2(std::string, glm::vec2);
	void setUniformVec3(std::string, glm::vec3);
	void setUniformVec4(std::string, glm::vec4);
	void setUniformMat4(std::string, glm::mat4);
};

std::string LoadShader(std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint CreateShader(const std::string& text, GLenum shaderType);

#endif
