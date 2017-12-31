#include "mesh.hpp"
using namespace glm;

Vertex::Vertex(const vec3 pos, const vec2 texCoord)
{
	this->pos = pos;
	this->texCoord = texCoord;
}
