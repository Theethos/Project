#include "pch.h"
#include "Axis.h"

Axis::Axis(const float size, const std::string & vertexShader, const std::string & fragmentShader) :
Drawable(vertexShader, fragmentShader)
{
	m_DrawType = GL_LINES;
	m_Vertices = std::vector<float>
	{
		// X-axis			
		0.f,  0.f,  0.f,		
		size, 0.f,  0.f,		
		// Y-axis		
		0.f,  0.f,  0.f,		
		0.f,  size, 0.f,		
		// Z-axis		
		0.f,  0.f,  0.f,		
		0.f,  0.f,  size	
	};
	m_Colors = std::vector<float>
	{
		// Red
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		// Green
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		// Blue
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
	};
}

Axis::Axis(const float size, Shader & shader) :
Drawable(shader)
{
	m_DrawType = GL_LINES;
	m_Vertices = std::vector<float>
	{
		// X-axis			
		0.f,  0.f,  0.f,
		size, 0.f,  0.f,
		// Y-axis		
		0.f,  0.f,  0.f,
		0.f,  size, 0.f,
		// Z-axis		
		0.f,  0.f,  0.f,
		0.f,  0.f,  size
	};
	m_Colors = std::vector<float>
	{
		// Red
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		// Green
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		// Blue
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
	};
}

Axis::~Axis()
{}
