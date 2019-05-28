#version 400 core

in vec3 in_Vertex;
in vec2 in_TextureCoord0;
in vec3 in_Normal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

out vec2 pass_TextureCoord0;
out vec3 surfaceNormal;
out vec3 toLightVector;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_Vertex, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	pass_TextureCoord0 = in_TextureCoord0;

	surfaceNormal = (transformationMatrix * vec4(in_Normal, 0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
}