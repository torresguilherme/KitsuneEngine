#include "shader.hpp"
using namespace std;

Shader::Shader(string vertShaderFile, string fragShaderFile/*, string geomShaderFile*/)
{
  program = glCreateProgram();
  if(program == 0)
  {
    std::cerr << "error: could not find a valid memory location for the shader program, shader creation failed!" << '\n';
    exit(5);
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
		exit(2);
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
		exit(4);
	}
}

GLuint CreateShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0)
	{
		cerr<<"error: shader creation failed"<<endl;
		exit(3);
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
