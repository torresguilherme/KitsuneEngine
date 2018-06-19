#version 130

uniform vec2 u_resolution;
uniform vec4 color;
uniform sampler2D diffuse;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
        vec3 sun = vec3(10.0, 3.0, 10.0);
        gl_FragColor = vec4((color * texture2D(diffuse, texCoord0))/(1/(dot(sun, normal0)/length(sun)*length(normal0)+1)));
}
