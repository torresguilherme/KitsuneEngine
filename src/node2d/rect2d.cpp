#include "rect2d.hpp"
using namespace std;
using namespace glm;

Rect2D::Rect2D(int width, int height, float red, float blue, float green, float alpha)
{
	this->width = width;
	this->height = height;
	this->color = vec4(red, blue, green, alpha);

	//i don't know if there's a more practical way to do that
	//but yeah what the hell
	vector<vec3> positions;
	positions.push_back(vec3((float) -width/2, (float) -height/2, 0.0));
	positions.push_back(vec3((float) -width/2, (float) height/2, 0.0));
	positions.push_back(vec3((float) width/2, (float) -height/2, 0.0));
	positions.push_back(vec3((float) width/2, (float) height/2, 0.0));

	vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);

	vector<vec2> texCoords;
	vector<vec3> normals;

	// initiallizing mesh
	mesh = new Mesh(positions, indices, texCoords, normals);

	// initializing shader
	shader = new Shader("", "");
	shader->addUniform("color");
	shader->setUniformVec4("color", this->color);
}

Rect2D::~Rect2D()
{
	delete mesh;
	delete shader;
}

void Rect2D::update(double delta)
{
}

void Rect2D::draw()
{
	shader->bind();
	mesh->draw();
}
