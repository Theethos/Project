#version 400 core

in vec2 in_Positions;

void main()
{
    gl_Position = vec4(in_Positions, 1.0, 1.0);
}
