#pragma once

#include "Drawable.h"

class GrassGround : public Drawable
{
public:
	GrassGround(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & texture = true, const bool & load = true);
	GrassGround(const float & size, Shader & shader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	~GrassGround();
};

class DirtGround : public Drawable
{
public:
	DirtGround(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	DirtGround(const float & size, Shader & shader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	~DirtGround();
};
