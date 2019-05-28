#version 400 core

in vec2 pass_TextureCoord0;
in vec3 surfaceNormal;
in vec3 toLightVector;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

out vec4 out_Color;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.0);
	vec3 diffuse = brightness * lightColor;

	out_Color = vec4(diffuse, 1.0) * texture(textureSampler, pass_TextureCoord0);
}

