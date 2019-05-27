#version 400 core

in vec2 TextureCoord0;

uniform sampler2D texture2D;

out vec4 out_Color;

void main()
{
	out_Color = texture(texture2D, TextureCoord0);
}

