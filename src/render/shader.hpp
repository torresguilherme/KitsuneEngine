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
	void setUniformVec3(std::string, glm::vec3);
	void setUniformMat4(std::string, glm::mat4);
};

std::string LoadShader(std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint CreateShader(const std::string& text, GLenum shaderType);

#endif
