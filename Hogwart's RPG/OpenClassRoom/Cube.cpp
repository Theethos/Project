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
		// Back face
		-size / 2.f, -size / 2.f, -size / 2.f,	// 0	0, 1, 2,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 1	0, 3, 2,
		 size / 2.f,  size / 2.f, -size / 2.f,	// 2
		-size / 2.f,  size / 2.f, -size / 2.f,	// 3
		// Right face
		 size / 2.f, -size / 2.f,  size / 2.f,	// 4	4, 5, 6,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 5	4, 7, 6,
		 size / 2.f,  size / 2.f, -size / 2.f,	// 6	
		 size / 2.f,  size / 2.f,  size / 2.f,	// 7
		// Bottom face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 8	8, 9, 10,
		 size / 2.f, -size / 2.f,  size / 2.f,	// 9	8, 11, 10,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 10
		-size / 2.f, -size / 2.f, -size / 2.f,	// 11
		// Front face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 12	15, 14, 13,
		 size / 2.f, -size / 2.f,  size / 2.f,	// 13	15, 12, 13,
		 size / 2.f,  size / 2.f,  size / 2.f,	// 14
		-size / 2.f,  size / 2.f,  size / 2.f,	// 15	
		// Left face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 16	16, 19, 18,
		-size / 2.f, -size / 2.f, -size / 2.f,	// 17	16, 17, 18,
		-size / 2.f,  size / 2.f, -size / 2.f,	// 18
		-size / 2.f,  size / 2.f,  size / 2.f,	// 19	
		// Top face
		-size / 2.f,  size / 2.f,  size / 2.f,	// 23	23, 20, 21,
		 size / 2.f,  size / 2.f,  size / 2.f,	// 22	23, 22, 21
		 size / 2.f,  size / 2.f, -size / 2.f,	// 21	
		-size / 2.f,  size / 2.f, -size / 2.f,	// 20	
	};
	m_Colors = std::vector<float>
	{
		// Face 1 -> Red
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		// Face 2 -> Green	
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		// Face 3 -> Blue	
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		// Face 4 -> Light Blue		
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		// Face 5 -> Yellow	
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		// Face 6 -> Pink
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
	};
	m_Indiced = true;
	m_Indices = std::vector<unsigned short>
	{
		0, 1, 2,
		0, 3, 2,

		4, 5, 6,
		4, 7, 6,

		8, 9, 10,
		8, 11, 10,

		15, 14, 13,
		15, 12, 13,

		16, 19, 18,
		16, 17, 18,

		23, 20, 21,
		23, 22, 21

	};
	if (load)
		Load();
}

Cube::Cube(const float size, Shader & shader, const bool & load) :
Drawable(shader)
{
	m_Vertices = std::vector<float>
	{
		// Back face
		-size / 2.f, -size / 2.f, -size / 2.f,	// 0	0, 1, 2,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 1	0, 3, 2,
		 size / 2.f,  size / 2.f, -size / 2.f,	// 2
		-size / 2.f,  size / 2.f, -size / 2.f,	// 3
		// Right face
		 size / 2.f, -size / 2.f,  size / 2.f,	// 4	4, 5, 6,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 5	4, 7, 6,
		 size / 2.f,  size / 2.f, -size / 2.f,	// 6	
		 size / 2.f,  size / 2.f,  size / 2.f,	// 7
		// Bottom face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 8	8, 9, 10,
		 size / 2.f, -size / 2.f,  size / 2.f,	// 9	8, 11, 10,
		 size / 2.f, -size / 2.f, -size / 2.f,	// 10
		-size / 2.f, -size / 2.f, -size / 2.f,	// 11
		// Front face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 12	15, 14, 13,
		 size / 2.f, -size / 2.f,  size / 2.f,	// 13	15, 12, 13,
		 size / 2.f,  size / 2.f,  size / 2.f,	// 14
		-size / 2.f,  size / 2.f,  size / 2.f,	// 15	
		// Left face
		-size / 2.f, -size / 2.f,  size / 2.f,	// 16	16, 19, 18,
		-size / 2.f, -size / 2.f, -size / 2.f,	// 17	16, 17, 18,
		-size / 2.f,  size / 2.f, -size / 2.f,	// 18
		-size / 2.f,  size / 2.f,  size / 2.f,	// 19	
		// Top face
		-size / 2.f,  size / 2.f,  size / 2.f,	// 23	23, 20, 21,
		 size / 2.f,  size / 2.f,  size / 2.f,	// 22	23, 22, 21
		 size / 2.f,  size / 2.f, -size / 2.f,	// 21	
		-size / 2.f,  size / 2.f, -size / 2.f,	// 20	
	};
	m_Colors = std::vector<float>
	{
		// Face 1 -> Red
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,
		// Face 2 -> Green	
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,
		// Face 3 -> Blue	
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,
		// Face 4 -> Light Blue		
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,
		// Face 5 -> Yellow	
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,
		// Face 6 -> Pink
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,
	};
	m_Indiced = true;
	m_Indices = std::vector<unsigned short>
	{
		0, 1, 2,
		0, 3, 2,

		4, 5, 6,
		4, 7, 6,

		8, 9, 10,
		8, 11, 10,

		15, 14, 13,
		15, 12, 13,

		16, 19, 18,
		16, 17, 18,

		23, 20, 21,
		23, 22, 21

	};
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
