#ifndef SHADER_HPP_
#define SHADER_HPP_
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

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

	std::string LoadBasicShader(int);

	public:
	Shader(std::string, std::string/*, std::string*/);
	~Shader();
	void bind();
	void update();
};

std::string LoadShader(std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint CreateShader(const std::string& text, GLenum shaderType);

#endif
