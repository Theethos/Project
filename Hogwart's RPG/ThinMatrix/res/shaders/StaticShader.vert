#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_textureCoordinates;
layout (location = 2) in vec3 in_normal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;//[4];
uniform bool useFakeLight;
uniform float numberOfRows;
uniform vec2 offset;
uniform vec4 plane;

out vec2 textureCoordinates;
out vec3 surfaceNormal;
out vec3 toLightVector;//[4];
out vec3 toCameraVector;
out float visibility;

const float fogDensity = 0.0035;
const float fogGradient = 5.0;


void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_position, 1.0);

	gl_ClipDistance[0] = dot(worldPosition, plane);

	vec4 positionRelativeToCam = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCam;
	textureCoordinates = (in_textureCoordinates / numberOfRows) + offset;

	if (useFakeLight)
		surfaceNormal = (transformationMatrix * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
	else
		surfaceNormal = (transformationMatrix * vec4(in_normal, 0.0)).xyz;
	
	//for (int i = 0; i < 4; ++i)
		//toLightVector[i] = lightPosition[i] - worldPosition.xyz;
		toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
	float distance = length(positionRelativeToCam.xyz);
	visibility = clamp(exp(-pow(distance * fogDensity, fogGradient)), 0.0, 1.0);
}