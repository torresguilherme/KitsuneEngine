#include "shader.hpp"
using namespace std;
using namespace glm;

Shader::Shader(string vertShaderFile, string fragShaderFile/*, string geomShaderFile*/)
{
	program = glCreateProgram();
	if(program == 0)
	{
		std::cerr << "error: could not find a valid memory location for the shader program, shader creation failed!" << '\n';
		exit(1);
	}
	string aux;

	aux = LoadShader(vertShaderFile);
	if(aux != "")
	{
		shaders[0] = CreateShader(aux, GL_VERTEX_SHADER);
	}
	else
	{
		shaders[0] = CreateShader(LoadBasicShader(0), GL_VERTEX_SHADER);
	}
	cout<<"vertex shader created successfully"<<endl;

	aux = LoadShader(fragShaderFile);
	if(aux != "")
	{
		shaders[1] = CreateShader(aux, GL_FRAGMENT_SHADER);
	}
	else
	{
		shaders[1] = CreateShader(LoadBasicShader(1), GL_FRAGMENT_SHADER);
	}
	cout<<"fragment shader created successfully"<<endl;

	/*
	   aux = LoadShader(geomShaderFile);
	   if(aux != "")
	   {
		   shaders[2] = CreateShader(aux, GL_GEOMETRY_SHADER);
	   }
	   else
	   {
		   shaders[2] = CreateShader(LoadBasicShader(2), GL_GEOMETRY_SHADER);
	   }
	   cout<<"geometry shader created successfully"<<endl;

*/
	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "error: the program could not be linked!");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "error: the program is not valid!");
}

Shader::~Shader()
{
	for(int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::update()
{
}

void Shader::addUniform(string name)
{
	GLuint uniformLocation = glGetUniformLocation(program, name.c_str());

	if(uniformLocation == (GLuint)-1)
	{
		cerr<<"error: could not find uniform: "<<name<<endl;
		exit(1);
	}

	uniforms.insert(pair<string, GLuint>(name, uniformLocation));
}

void Shader::setUniformi(string name, int value)
{
	glUniform1i(uniforms.find(name)->second, value);
}

void Shader::setUniformf(string name, float value)
{
	glUniform1f(uniforms.find(name)->second, value);
}

void Shader::setUniformVec3(string name, vec3 value)
{
	glUniform3f(uniforms.find(name)->second, value.x, value.y, value.z);
}

void Shader::setUniformMat4(string name, mat4 value)
{
	glUniformMatrix4fv(uniforms.find(name)->second, 1, GL_FALSE, &value[0][0]);
}

string Shader::LoadBasicShader(int type)
{
	ifstream file;
	if(type == 0)
	{
		file.open(basicVertShader);
	}
	else if(type == 1)
	{
		file.open(basicFragShader);
	}
	else
	{
		file.open(basicGeomShader);
	}

	string output;
	string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}

	else
	{
		cout<<"error: couldn't find the basic shader file"<<endl;
		exit(1);
	}
	return output;
}

string LoadShader(string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}

	else
	{
		cout<<"couldn't find the shader file!"<<endl;
		return "";
	}

	return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = {0};

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr<<errorMessage<<": '"<<error<<"'"<<endl;
		exit(1);
	}
}

GLuint CreateShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0)
	{
		cerr<<"error: shader creation failed"<<endl;
		exit(1);
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLenghts[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLenghts[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLenghts);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "error: shader couldn't be compiled");

	return shader;
}
