#version 150 core

in vec3 in_Vertex;
in vec2 in_TextureCoord0;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 pass_TextureCoord0;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(in_Vertex, 1.0);

	pass_TextureCoord0 = in_TextureCoord0;
}