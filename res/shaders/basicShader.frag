#version 130

out vec4 fragColor;
uniform float uni;

void main()
{
  float alpha = uni;
  fragColor = vec4(0.0, 1.0, 1.0, alpha);
}
