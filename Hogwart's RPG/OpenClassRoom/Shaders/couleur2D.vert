#version 150 core

in vec2 in_Vertex;
in vec3 in_Color;

out vec4 Color;

void main()
{
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
	Color = vec4(in_Color, 1.0);
}