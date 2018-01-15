#version 130

in vec3 position;
uniform mat4 transform;

void main()
{
	gl_Position = vec4(0.5 * position, 1.0);
}
