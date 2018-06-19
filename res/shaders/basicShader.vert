#version 130

in vec3 position;
in vec2 texCoord;
in vec3 normal;
uniform mat4 transform;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = normal;
}
