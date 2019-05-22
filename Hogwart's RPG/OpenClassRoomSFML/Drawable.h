#pragma once

#include "Shader.h"


class Drawable
{
public:
	virtual void Draw(glm::mat4 & modelView, glm::mat4 projection);
protected:
	Drawable(const std::string & vertexShader, const std::string & fragmentShader);
	Drawable(Shader & shader);
	virtual ~Drawable();

	unsigned m_DrawType;
	Shader m_Shader;
	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;
};
