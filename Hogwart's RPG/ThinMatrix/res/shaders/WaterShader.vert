#version 400 core

layout (location = 0) in vec2 in_position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;	
uniform vec3 lightPosition;

const float tiling = 20.0;

void main()
{
	vec4 worldPosition = modelMatrix * vec4(in_position.x, 0.0, in_position.y, 1.0);
	textureCoords = vec2(in_position.x / 2.0 + 0.5, in_position.y / 2.0 + 0.5) * tiling;
	clipSpace = projectionMatrix * viewMatrix * worldPosition;
	gl_Position = clipSpace;
	toCameraVector = cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - lightPosition;
}