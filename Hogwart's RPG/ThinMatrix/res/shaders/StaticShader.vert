#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_textureCoordinates;
layout (location = 2) in vec3 in_normal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform bool useFakeLight;

out vec2 textureCoordinates;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

const float fogDensity = 0.0035;
const float fogGradient = 5.0;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_position, 1.0);
	vec4 positionRelativeToCam = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCam;
	textureCoordinates = in_textureCoordinates;

	if (useFakeLight)
		surfaceNormal = (transformationMatrix * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
	else
		surfaceNormal = (transformationMatrix * vec4(in_normal, 0.0)).xyz;
	
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
	float distance = length(positionRelativeToCam.xyz);
	visibility = clamp(exp(-pow(distance * fogDensity, fogGradient)), 0.0, 1.0);
}