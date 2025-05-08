#version 330 core

uniform vec4 u_Color;

out vec4 v_FragColor;

void main()
{
    v_FragColor = u_Color;
    // v_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
