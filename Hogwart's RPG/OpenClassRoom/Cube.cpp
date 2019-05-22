#include "pch.h"
#include "Cube.h"


Cube::Cube(const float size, const char * vertexShader, const char * fragmentShader) :
Drawable(vertexShader, fragmentShader)
{
	m_DrawType = GL_TRIANGLES;
	m_Vertices = std::vector<float>
	{
		-size / 2.f, -size / 2.f, -size / 2.f,	  size / 2.f, -size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	// Face 1-1
		-size / 2.f, -size / 2.f, -size / 2.f,	  size / 2.f,  size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 1-2

		 size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	   size / 2.f, -size / 2.f, -size / 2.f,	// Face 2-1
		 size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	// Face 2-2

		-size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f, -size / 2.f,	// Face 3-1
		-size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f, -size / 2.f, -size / 2.f,   -size / 2.f, -size / 2.f, -size / 2.f,	// Face 3-2

		-size / 2.f,  size / 2.f,  size / 2.f,   -size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f,  size / 2.f,	// Face 4-1
		-size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f,  size / 2.f,	// Face 4-2

		-size / 2.f, -size / 2.f,  size / 2.f,   -size / 2.f,  size / 2.f,  size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 5-1
		-size / 2.f, -size / 2.f,  size / 2.f,   -size / 2.f, -size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 5-2

		-size / 2.f,  size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f,	// Face 6-1
		-size / 2.f,  size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f		// Face 6-2
	};
	m_Colors = std::vector<float>
	{
		// Face 1			-> Red
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		// Face 2			-> Green
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		// Face 3			-> Blue
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		// Face 4			-> Light-Blue
		0.f,  1.f,  1.f,	0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,    0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		// Face 5			-> Yellow
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		// Face 6			-> Rose
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f,
	};
}

Cube::Cube(const float size, Shader & shader) : 
Drawable(shader)
{
	m_DrawType = GL_TRIANGLES;
	m_Vertices = std::vector<float>
	{
		-size / 2.f, -size / 2.f, -size / 2.f,	  size / 2.f, -size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	// Face 1-1
		-size / 2.f, -size / 2.f, -size / 2.f,	  size / 2.f,  size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 1-2

		 size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	   size / 2.f, -size / 2.f, -size / 2.f,	// Face 2-1
		 size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,	// Face 2-2

		-size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f, -size / 2.f,	// Face 3-1
		-size / 2.f, -size / 2.f,  size / 2.f,	  size / 2.f, -size / 2.f, -size / 2.f,   -size / 2.f, -size / 2.f, -size / 2.f,	// Face 3-2

		-size / 2.f,  size / 2.f,  size / 2.f,   -size / 2.f, -size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f,  size / 2.f,	// Face 4-1
		-size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f, -size / 2.f,  size / 2.f,	// Face 4-2

		-size / 2.f, -size / 2.f,  size / 2.f,   -size / 2.f,  size / 2.f,  size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 5-1
		-size / 2.f, -size / 2.f,  size / 2.f,   -size / 2.f, -size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f, -size / 2.f,	// Face 5-2

		-size / 2.f,  size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f, -size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f,	// Face 6-1
		-size / 2.f,  size / 2.f, -size / 2.f,   -size / 2.f,  size / 2.f,  size / 2.f,    size / 2.f,  size / 2.f,  size / 2.f		// Face 6-2
	},
	m_Colors = std::vector<float>
	{
		// Face 1			-> Red
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		// Face 2			-> Green
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		// Face 3			-> Blue
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		// Face 4			-> Light-Blue
		0.f,  1.f,  1.f,	0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,    0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		// Face 5			-> Yellow
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		// Face 6			-> Rose
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f,
	};
}

Cube::~Cube() {}

