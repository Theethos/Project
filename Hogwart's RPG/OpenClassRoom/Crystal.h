#pragma once

#include "Drawable.h"

class Crystal : public Drawable
{
public:
	Crystal(const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	Crystal(Shader & shader, const unsigned & textureID, const bool & textured = true, const bool & load = true);
	~Crystal();

	void Animate();

private:
	float m_RotationAngle;
};

