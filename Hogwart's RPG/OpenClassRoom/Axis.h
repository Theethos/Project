#pragma once

#include "Drawable.h"

class Axis : public Drawable
{
public:
	Axis(const float size, const char * vertexShader, const char * fragmentShader, const bool & load = true);
	Axis(const float size, Shader & shader, const bool & load = true);
	~Axis();
};

