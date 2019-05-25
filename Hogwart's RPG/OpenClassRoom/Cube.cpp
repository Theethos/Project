#include "pch.h"
#include "Cube.h"

/////////////////
/// Cube class
/////////////////
Cube::Cube(const float size, const char * vertexShader, const char * fragmentShader, const bool & load) :
Drawable(vertexShader, fragmentShader)
{
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
	if (load)
		Load();
}

Cube::Cube(const float size, Shader & shader, const bool & load) :
Drawable(shader)
{
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
		1.f,  0.f,  0.f,	1.f,  0.f,  0.f,	1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,	1.f,  0.f,  0.f,	1.f,  0.f,  0.f,
		// Face 2			-> Green
		0.f,  1.f,  0.f,	0.f,  1.f,  0.f,	0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,	0.f,  1.f,  0.f,	0.f,  1.f,  0.f,
		// Face 3			-> Blue
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,	0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,	0.f,  0.f,  1.f,	0.f,  0.f,  1.f,
		// Face 4			-> Light-Blue
		0.f,  1.f,  1.f,	0.f,  1.f,  1.f,	0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,	0.f,  1.f,  1.f,	0.f,  1.f,  1.f,
		// Face 5			-> Yellow
		1.f,  1.f,  0.f,	1.f,  1.f,  0.f,	1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,	1.f,  1.f,  0.f,	1.f,  1.f,  0.f,
		// Face 6			-> Rose
		1.f,  0.f,  1.f,	1.f,  0.f,  1.f,	1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,	1.f,  0.f,  1.f,	1.f,  0.f,  1.f,
	};
	/*m_Vertices = std::vector<float>
	{
		 size / 2.f,  size / 2.f,  size / 2.f,
		 size / 2.f,  size / 2.f, -size / 2.f,
		 size / 2.f, -size / 2.f,  size / 2.f,
		 size / 2.f, -size / 2.f, -size / 2.f,
		-size / 2.f,  size / 2.f,  size / 2.f,
		-size / 2.f,  size / 2.f, -size / 2.f,
		-size / 2.f, -size / 2.f,  size / 2.f,
		-size / 2.f, -size / 2.f, -size / 2.f,
	};
	m_VerticesIndices = std::vector<unsigned short>
	{
		7, 3, 1,
		7, 1, 5,

		2, 1, 3,
		2, 0, 1,

		6, 2, 3,
		6, 3, 7,

		4, 6, 2,
		4, 0, 2,

		6, 4, 5,
		6, 7, 5,

		5, 1, 0,
		5, 4, 0,
	};
	m_Colors = std::vector<float>
	{
		1.f,  0.f,  0.f,
		0.f,  1.f,  0.f,
		0.f,  0.f,  1.f,
		0.f,  1.f,  1.f,
		1.f,  1.f,  0.f,
		1.f,  0.f,  1.f,
	};
	m_ColorsIndices = std::vector<unsigned short>
	{
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5,
	};*/

	if (load)
		Load();
}

Cube::~Cube() 
{}

/////////////////
/// Square class
/////////////////
Square::Square(const float size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured, const bool & load) :
	Drawable(vertexShader, fragmentShader)
{
	m_Vertices = std::vector<float>
	{
		-size / 2, -size / 2, -size / 2,   size / 2, -size / 2, -size / 2,   size / 2, size / 2, -size / 2,
		-size / 2, -size / 2, -size / 2,   -size / 2, size / 2, -size / 2,   size / 2, size / 2, -size / 2
	};

	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0, 0,   1, 0,   1, 1,
			0, 0,   0, 1,   1, 1
		};
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

Square::Square(const float size, Shader & shader, const unsigned & textureID, const bool & textured, const bool & load) :
	Drawable(shader)
{
	m_Vertices = std::vector<float>
	{ 
		- size / 2, - size / 2, - size / 2,   size / 2, - size / 2, - size / 2,   size / 2, size / 2, - size / 2,     
		- size / 2, - size / 2, - size / 2,   - size / 2, size / 2, - size / 2,   size / 2, size / 2, - size / 2 
	};

	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0, 0,   1, 0,   1, 1,
			0, 0,   0, 1,   1, 1
		};
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

Square::~Square()
{
}
