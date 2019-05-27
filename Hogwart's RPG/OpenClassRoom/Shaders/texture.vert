#version 400 core

in vec3 in_Vertex;
in vec2 in_TextureCoord0;

uniform mat4 modelviewProjection;

out vec2 TextureCoord0;

void main()
{
	gl_Position = modelviewProjection * vec4(in_Vertex, 1.0);

	TextureCoord0 = in_TextureCoord0;
}