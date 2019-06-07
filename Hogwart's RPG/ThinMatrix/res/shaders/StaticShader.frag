#version 400 core

in vec2 textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

uniform sampler2D modelTexture;
uniform vec3 lightColor;
uniform float shininess;
uniform float reflectivity;
uniform vec3 skyColor;

out vec4 out_Color;

void main()
{
	vec4 texture_color = texture(modelTexture, textureCoordinates);
	if (texture_color.a < 0.5 || visibility == 0)
		discard;
	
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

	out_Color = vec4(diffuse, 1.0) * texture_color + vec4(specular, 1.0);
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}

