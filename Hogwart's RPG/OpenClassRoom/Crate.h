#pragma once

#include "Cube.h"

class Crate : public Cube
{
public:
	Crate(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	Crate(const float & size, Shader & shader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	~Crate();
};

