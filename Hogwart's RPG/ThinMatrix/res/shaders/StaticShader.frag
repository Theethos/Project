#version 400 core

in vec2 textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector;//[4];
in vec3 toCameraVector;
in float visibility;

uniform sampler2D modelTexture;
uniform vec3 lightColor;//[4];
uniform vec3 attenuation;//[4];
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
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	//for (int i = 0; i < 4; ++i)
	//{
		//float distance = length(toLightVector[i]);
		float distance = length(toLightVector);
		//float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance); 
		float attFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance); 
		//vec3 unitLightVector = normalize(toLightVector[i]);
		vec3 unitLightVector = normalize(toLightVector);
		float brightness = max(dot(unitNormal, unitLightVector), 0.0);
		vec3 lightDirection = - unitLightVector;  
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = pow(max(dot(reflectedLightDirection, unitVectorToCamera), 0.0), shininess);
	
		//diffuse += (brightness * lightColor[i]) / attFactor;
		diffuse += (brightness * lightColor) / attFactor;
		//specular += (specularFactor * reflectivity * lightColor[i]) / attFactor;
		specular += (specularFactor * reflectivity * lightColor) / attFactor;
	//}

	diffuse = max(diffuse, 0.2); // AMBIENT_LIGHT

	out_Color = vec4(diffuse, 1.0) * texture_color + vec4(specular, 1.0);
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}

