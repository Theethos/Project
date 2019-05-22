#pragma once

#include "Cube.h"

class Crate : public Cube
{
public:
	Crate(const float & size, const char * vertexShader, const char * fragmentShader, unsigned & texture);
	Crate(const float & size, Shader & shader, unsigned & texture);
	~Crate();

	void Draw();

private:
	unsigned m_Texture;
	std::vector<float> m_TextureCoordinates;
};

