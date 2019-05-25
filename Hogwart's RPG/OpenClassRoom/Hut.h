#pragma once

#include "Drawable.h"

class Hut : public Drawable
{
public:
	Hut(const char * vertexShader, const char * fragmentShader, const unsigned & wallTextureID, const unsigned & roofTextureID, const bool & textured = true, const bool & load = true);
	Hut(Shader & shader, const unsigned & wallTextureID, const unsigned & roofTextureID, const bool & textured = true, const bool & load = true);
	~Hut();
};

