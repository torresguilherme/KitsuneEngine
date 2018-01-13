#version 130

in vec3 position;

void main()
{
	gl_Position = vec4(0.5 * position, 1.0);
}
