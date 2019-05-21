#pragma once

#include "Drawable.h"

class Axis : public Drawable
{
public:
	Axis(const float size, const std::string & vertexShader, const std::string & fragmentShader);
	Axis(const float size, Shader & shader);
	~Axis();
};

