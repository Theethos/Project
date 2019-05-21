#pragma once

#include "Drawable.h"

class Cube : public Drawable
{
public:
	Cube(const float size, const std::string & vertexShader, const std::string & fragmentShader);
	Cube(const float size, Shader & shader);
	~Cube();
};

