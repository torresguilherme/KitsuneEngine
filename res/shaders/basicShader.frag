#version 130

uniform vec2 u_resolution;

void main()
{
        vec2 st = gl_FragCoord.xy/u_resolution;
        gl_FragColor = vec4(st.x, st.y, 0.0, 0.5);
}
