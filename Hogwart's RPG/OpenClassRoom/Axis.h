#pragma once

#include "Drawable.h"

class Axis : public Drawable
{
public:
	Axis(const float size, const char * vertexShader, const char * fragmentShader);
	Axis(const float size, Shader & shader);
	~Axis();
};

