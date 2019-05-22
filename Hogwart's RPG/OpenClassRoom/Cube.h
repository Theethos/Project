#pragma once

#include "Drawable.h"

class Cube : public Drawable
{
public:
	Cube(const float size, const char * vertexShader, const char * fragmentShader);
	Cube(const float size, Shader & shader);
	~Cube();
};

