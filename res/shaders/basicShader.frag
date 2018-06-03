#version 130

uniform vec2 u_resolution;
uniform vec4 color;
uniform sampler2D diffuse;

varying vec2 texCoord0;

void main()
{
        gl_FragColor = vec4(color * texture2D(diffuse, texCoord0));
}
