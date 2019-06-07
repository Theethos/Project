#version 400 core

in vec2 textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

uniform sampler2D rColor;
uniform sampler2D gColor;
uniform sampler2D bColor;
uniform sampler2D bgColor;
uniform sampler2D blendMap;

uniform vec3 lightColor;
uniform float shininess;
uniform float reflectivity;
uniform vec3 skyColor;

out vec4 out_Color;

void main()
{
	if (visibility == 0)
		discard;

	vec4 blendMapColor = texture(blendMap, textureCoordinates);
	float bgTexAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tileCoords = textureCoordinates * 40.0;
	vec4 bgTexColor = texture(bgColor, tileCoords) * bgTexAmount;
	vec4 rTexColor = texture(rColor, tileCoords) * blendMapColor.r;
	vec4 gTexColor = texture(gColor, tileCoords) * blendMapColor.g;
	vec4 bTexColor = texture(bColor, tileCoords) * blendMapColor.b;

	vec4 totalColor = bgTexColor + rTexColor + gTexColor + bTexColor;

	// Diffuse
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float brightness = max(dot(unitNormal, unitLightVector), 0.2); // 0.2 = AMBIENT LIGHTING
	vec3 diffuse = brightness * lightColor;

	// Specular
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = - unitLightVector;  
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	float specularFactor = pow(max(dot(reflectedLightDirection, unitVectorToCamera), 0.0), shininess);
	vec3 specular = specularFactor * reflectivity * lightColor;

	out_Color = vec4(diffuse, 1.0) * totalColor + vec4(specular, 1.0);
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}
