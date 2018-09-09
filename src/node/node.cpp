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

#include "node.hpp"
using namespace glm;
using namespace std;

Transform::Transform()
{
	translation = vec3(0.0, 0.0, 0.0);
	rotation = vec3(0.0, 0.0, 0.0);
	scale = vec3(1.0, 1.0, 1.0);
}

Transform::~Transform()
{
}

mat4 Transform::getTransformation()
{
	mat4 m_transformation(1.0);
	m_transformation = glm::translate(m_transformation, this->translation);

	mat4 m_rotationX = glm::rotate(rotation.x, vec3(1.0, 0.0, 0.0));
	mat4 m_rotationY = glm::rotate(rotation.y, vec3(0.0, 1.0, 0.0));
	mat4 m_rotationZ = glm::rotate(rotation.z, vec3(0.0, 0.0, 1.0));
	mat4 m_rotation = m_rotationZ * m_rotationY * m_rotationX;

	mat4 m_scale(1.0);
	m_scale = glm::scale(m_scale, this->scale);

	return m_transformation * m_rotation * m_scale;
}

Node::Node()
{
	pauseMode = INHERIT;
	parent = NULL;

	shader = new Shader("", "");
	shader->addUniform("transform");
	shader->addUniform("color");

	colorR = 1.0;
	colorG = 1.0;
	colorB = 1.0;
	colorA = 1.0;

	hasScript = false;
	mesh = NULL;
	texture = NULL;

	// transform test
	//setScale(0.5, 0.5, 0.5);
}

Node::~Node()
{
	if(mesh)
	{
		delete mesh;
	}

	delete shader;

	if(texture)
	{
		delete texture;
	}

	if (hasScript)
	{
		lua_close(state);
	}
}

void Node::update(double delta)
{
	if(hasScript)
	{
		lua_pushnumber(state, delta);
		lua_setglobal(state, "delta");
		lua_getglobal(state, "_update");
		lua_pcall(state, 0, LUA_MULTRET, 0);
	}

	for(int i = 0; i < children.size(); i++)
	{
		children[i]->update(delta);
	}
}

void Node::draw(mat4 fatherMvp, mat4 projectionMat, mat4 viewMat)
{
	mat4 thisMvp = projectionMat * viewMat * transform.getTransformation();
	shader->bind();
	shader->setUniformMat4("transform", thisMvp);
	shader->setUniformVec4("color", vec4(colorR, colorG, colorB, colorA));

	if(texture)
	{
		texture->bind(0);
	}

	if(mesh)
	{
		mesh->draw();
	}

	for(int i = 0; i < children.size(); i++)
	{
		children[i]->draw(thisMvp, projectionMat, viewMat);
	}
}

int Node::attachScript(string fileName)
{
	state = luaL_newstate();
	luaL_openlibs(state);
	// register API functions
	lua_pushlightuserdata(state, this);
	lua_setglobal(state, "_self");
	lua_register(state, "getPos", Node::getPosL);
	lua_register(state, "getGlobalPos", Node::getGlobalPosL);
	lua_register(state, "setPos", Node::setPosL);
	lua_register(state, "move", Node::moveL);
	//lua_register(state, "getRot", Node::getRotL);
	lua_register(state, "setRot", Node::setRotL);
	lua_register(state, "rotateEulerAngles", Node::rotateEulerAnglesL);
	//lua_register(state, "rotateQuaternion", Node::rotateQuaternionL);
	//lua_register(state, "getScale", Node::getScaleL);
	lua_register(state, "setScale", Node::setScaleL);
	lua_register(state, "scale", Node::scaleL);
	
	int s = luaL_loadfile(state, fileName.c_str());
	if(s == LUA_OK)
	{
		lua_pcall(state, 0, LUA_MULTRET, 0);
		hasScript = true;
		return 0;
	}

	else
	{
		cerr<<"Error: "<<lua_tostring(state, -1)<<endl;
		lua_pop(state, 1);
		return 1;
	}
}

/*
 * LUA NATIVE FUNCTIONS
 */

void Node::addChild(Node *newChild)
{
	children.push_back(newChild);
	newChild->parent = this;
}

int Node::removeChild(Node *child)
{
	for(unsigned int i = 0; i < children.size(); i++)
	{
		if(children[i] == child)
		{
			free(children[i]);
			children.erase(children.begin()+i);
			return 0;
		}
	}

	cout<<"Child to be removed not found"<<endl;
	return 1;
}

mat4 Node::getGlobalMatrix()
{
	if(this->parent == NULL)
	{
		return transform.getTransformation();
	}
	else
	{
		return parent->getGlobalMatrix() * transform.getTransformation();
	}
}

vec3 Node::getPos()
{
	return transform.translation;
}

vec3 Node::getGlobalPos()
{
	mat4 globalMatrix = getGlobalMatrix();
	return vec3(globalMatrix[3][0], globalMatrix[3][1], globalMatrix[3][2]);
}

void Node::setPos(float x, float y, float z)
{
	transform.translation = vec3(x, y, z);
}

void Node::move(vec3 dir)
{
	setPos(getPos().x + dir.x, getPos().y + dir.y, getPos().z + dir.z);
}

vec3 Node::getRot()
{
	return transform.rotation;
}

void Node::setRot(float x, float y, float z)
{
	transform.rotation = vec3(x, y, z);
}

vec3 Node::getScale()
{
	return transform.scale;
}

void Node::setScale(float x, float y, float z)
{
	transform.scale = vec3(x, y, z);
}

/*
 * LUA API FUNCTIONS
 */

// to do: usar metatables para os retornos das funçoes get que retornam vetor
// to do: getNodeL, addChildL, removeChildL

int Node::getPosL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -1);
	lua_pushnumber(state, node->getPos().x);
	lua_pushnumber(state, node->getPos().y);
	lua_pushnumber(state, node->getPos().z);
	return 3;
}

int Node::getGlobalPosL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -1);
	lua_pushnumber(state, node->getGlobalPos().x);
	lua_pushnumber(state, node->getGlobalPos().y);
	lua_pushnumber(state, node->getGlobalPos().z);
	return 3;
}

int Node::setPosL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->setPos(x, y, z);
	return 0;
}

int Node::moveL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->move(vec3(x, y, z));
	return 0;
}

// todo: getRotL, rotateQuaternionL

int Node::setRotL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->setRot(x, y, z);
	return 0;
}

int Node::rotateEulerAnglesL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->setRot(node->getRot().x + x, node->getRot().y + y, node->getRot().z + z);
	return 0;
}

// todo: getScaleL

int Node::setScaleL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->setRot(x, y, z);
	return 0;
}

int Node::scaleL(lua_State* state)
{
	Node* node = (Node*) lua_touserdata(state, -4);
	float x = lua_tonumber(state, -3);
	float y = lua_tonumber(state, -2);
	float z = lua_tonumber(state, -1);
	node->setScale(node->getScale().x * x, node->getScale().y * y, node->getScale().z * z);
	return 0;
}

/*
 * END
 */

inline double deg2rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

inline double rad2deg(double radians)
{
	return radians * (180.0 / M_PI);
}

/*
 * OBJ LOADER -> to do: refatorar isso aqui
 */

Mesh *loadMesh(string sFileName)
{
	const char *fileName = sFileName.c_str();
	FILE* file;
	file = fopen(fileName, "r");

	char line[256];
	vector<vec3> vertices;
	vector<int> faceIndices;
	vector<int> vertexIndices;
	vector<int> uvIndices;
	vector<int> normalIndices;
	vector<vec2> texCoords;
	vector<vec3> normals;
	float data[4];
	int vI[3];
	int uvI[3];
	int nI[3];

	if(!file)
	{
		cerr<<"error: could not find mesh file to import: "<<fileName<<endl;
		exit(1);
	}

	// import obj
	Mesh *ret;
	const char *ext = &fileName[0];
	int i = strlen(fileName);

	while(*ext != '\0')
	{
		ext++;
	}

	while(*ext != '.')
	{
		if(i <= 0)
		{
			cerr<<"error: mesh file does not have an extention"<<endl;
			exit(1);
		}

		ext--;
		i--;
	}

	if(!strcmp(ext, ".obj"))
	{
		bool hasUVs = false;
		bool hasNormals = false;
		while(fscanf(file, "%s", line) != EOF)
		{
			if(!strcmp(line, "v"))
			{
				fscanf(file, "%f %f %f\n", &data[0], &data[1], &data[2]);
				vertices.push_back(vec3(data[0], data[1], data[2]));
			}

			else if(!strcmp(line, "vt"))
			{
				hasUVs = true;
				fscanf(file, "%f %f\n", &data[0], &data[1]);
				texCoords.push_back(vec2(data[0], data[1]));
			}

			else if(!strcmp(line, "vn"))
			{
				hasNormals = false;
				fscanf(file, "%f %f %f\n", &data[0], &data[1], &data[2]);
				normals.push_back(vec3(data[0], data[1], data[2]));
			}

			else if(!strcmp(line, "f"))
			{
				int matches = fscanf(file, "%i/%i/%i %i/%i/%i %i/%i/%i\n", &vI[0], &uvI[0], &nI[0], &vI[1], &uvI[1], &nI[1], &vI[2], &uvI[2], &nI[2]);

				if(matches != 9)
				{
					cerr<<"Error:can't load the obj file with the given export options, please try something else"<<endl;
					return NULL;
				}
				
				for(int i = 0; i < 3; i++)
				{
					vertexIndices.push_back(vI[i] - 1);
					uvIndices.push_back(uvI[i] - 1);
					normalIndices.push_back(nI[i] - 1);
				}
			}
		}
	}

	else
	{
		cerr<<"error: mesh export format is not supported"<<endl;
		exit(1);
	}

	ret = new Mesh(vertices, vertexIndices, texCoords, uvIndices, normals, normalIndices);
	return ret;
}

Texture *loadTexture(string fileName)
{
	Texture *ret = new Texture(fileName);
	return ret;
}
