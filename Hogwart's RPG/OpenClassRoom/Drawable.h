#pragma once

#include "Shader.h"


class Drawable
{
public:
	virtual void Draw();
protected:
	Drawable(const char * vertexShader, const char * fragmentShader);
	Drawable(Shader & shader);
	virtual ~Drawable();

	unsigned m_DrawType;
	Shader m_Shader;
	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;
};
