#pragma once

#include "Drawable.h"

class Cube : public Drawable
{
public:
	Cube(const float size, const char * vertexShader, const char * fragmentShader, const bool & load = true);
	Cube(const float size, Shader & shader, const bool & load = true);
	~Cube();
};

class Square : public Drawable
{
public:
	Square(const float size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	Square(const float size, Shader & shader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	~Square();
};