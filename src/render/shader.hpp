#ifndef SHADER_HPP_
#define SHADER_HPP_
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

const char* basicVertShader = "./res/shaders/basicShader.vert";
const char* basicFragShader = "./res/shaders/basicShader.frag";
const char* basicGeomShader = "./res/shaders/basicShader.geom";

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

	std::string LoadBasicShader(int);

	public:
	Shader(std::string, std::string/*, std::string*/);
	~Shader();
	void Bind();
	void Update();
};

static std::string LoadShader(std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

#endif
