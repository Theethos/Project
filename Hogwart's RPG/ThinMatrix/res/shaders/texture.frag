#version 150 core

in vec2 pass_TextureCoord0;

uniform sampler2D textureSampler;

out vec4 out_Color;

void main()
{
	out_Color = texture(textureSampler, pass_TextureCoord0);
}

