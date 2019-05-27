#pragma once

#include "Shader.h"
#include "Entity.h"

class Renderer
{
public:
	Renderer(Shader & shader);
	~Renderer();

	void Render(const Entity & model);

private:
	Shader & m_Shader;
	glm::mat4 m_ProjectionMatrix;
	double m_Fov;
	double m_AspectRatio;
	double m_Near, m_Far;
};

