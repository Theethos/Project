#version 150 core

in vec3 in_Vertex;
in vec3 in_Color;

uniform mat4 modelviewProjection;

out vec4 Color;

void main()
{
	gl_Position =  modelviewProjection * vec4(in_Vertex, 1.0);
	Color = vec4(in_Color, 1.0);
}