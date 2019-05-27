#include "pch.h"
#include "Hut.h"


Hut::Hut(const char * vertexShader, const char * fragmentShader, const unsigned & wallTextureID, const unsigned & roofTextureID, const bool & textured, const bool & load) :
Drawable(vertexShader, fragmentShader)
{
	m_Vertices = std::vector<float>
	{
		// Right wall
		 5.f,  0.f,  5.f,	// 0	0, 1, 2,
		 5.f,  5.f,  5.f,	// 1	0, 3, 2,
		 5.f,  5.f, -5.f,	// 2
		 5.f,  0.f, -5.f,	// 3
		// Back wall
		 5.f,  5.f, -5.f,	// 4	4, 5, 6,
		 5.f,  0.f, -5.f,	// 5	4, 7, 6,
		-5.f,  0.f, -5.f,	// 6
		-5.f,  5.f, -5.f,	// 7
		// Left wall
		-5.f,  5.f, -5.f,	// 8	8, 9, 10,
		-5.f,  5.f,  5.f,	// 9	8, 11, 10,
		-5.f,  0.f,  5.f,	// 10
		-5.f,  0.f, -5.f,	// 11
		// Back loft (les combles)
		-5.f,  5.f, -5.f,	// 12	12, 13, 14,
		 0.f,  6.f,  -5.f,	// 13
		 5.f,  5.f, -5.f,	// 14
		// Left side roof
		-6.f, 4.8f, -6.f,	// 15	15, 16, 17,
		 0.f,  6.f, -6.f,	// 16	15, 18, 17,
		 0.f,  6.f,  6.f,	// 17
		-6.f, 4.8f,  6.f,	// 18
		// Right side roof
		 0.f,  6.f, -6.f,	// 19	19, 20, 21,
		 6.f, 4.8f, -6.f,	// 20	19, 22, 21,
		 6.f, 4.8f,  6.f,	// 21
		 0.f,  6.f,  6.f,	// 22 
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

		12, 13, 14,

		15, 16, 17,
		15, 18, 17,

		19, 20, 21,
		19, 22, 21,
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Right wall
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			// Back wall
			0.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			// Left wall
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			// Back loft
			0.f, 0.f,
			0.5f, 0.5f,
			1.f, 0.f,
			// Left side roof
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			// Rigth side roof
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};
		// Two textures : roof and walls
		m_Textures.push_back(std::make_pair(wallTextureID, 21));
		m_Textures.push_back(std::make_pair(roofTextureID, 12));
	}
	if (load)
		Load();
}

Hut::Hut(Shader & shader, const unsigned & wallTextureID, const unsigned & roofTextureID, const bool & textured, const bool & load) :
Drawable(shader)
{
	m_Vertices = std::vector<float>
	{
		// Right wall
		 5.f,  0.f,  5.f,	// 0	0, 1, 2,
		 5.f,  5.f,  5.f,	// 1	0, 3, 2,
		 5.f,  5.f, -5.f,	// 2
		 5.f,  0.f, -5.f,	// 3
		// Back wall
		 5.f,  5.f, -5.f,	// 4	4, 5, 6,
		 5.f,  0.f, -5.f,	// 5	4, 7, 6,
		-5.f,  0.f, -5.f,	// 6
		-5.f,  5.f, -5.f,	// 7
		// Left wall
		-5.f,  5.f, -5.f,	// 8	8, 9, 10,
		-5.f,  5.f,  5.f,	// 9	8, 11, 10,
		-5.f,  0.f,  5.f,	// 10
		-5.f,  0.f, -5.f,	// 11
		// Back loft (les combles)
		-5.f,  5.f, -5.f,	// 12	12, 13, 14,
		 0.f,  6.f,  -5.f,	// 13
		 5.f,  5.f, -5.f,	// 14
		// Left side roof
		-6.f, 4.8f, -6.f,	// 15	15, 16, 17,
		 0.f,  6.f, -6.f,	// 16	15, 18, 17,
		 0.f,  6.f,  6.f,	// 17
		-6.f, 4.8f,  6.f,	// 18
		// Right side roof
		 0.f,  6.f, -6.f,	// 19	19, 20, 21,
		 6.f, 4.8f, -6.f,	// 20	19, 22, 21,
		 6.f, 4.8f,  6.f,	// 21
		 0.f,  6.f,  6.f,	// 22 
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

		12, 13, 14,

		15, 16, 17,
		15, 18, 17,

		19, 20, 21,
		19, 22, 21,
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Right wall
			0.f, 0.f,	
			0.f, 1.f,	
			1.f, 1.f,
			1.f, 0.f,
			// Back wall
			0.f, 1.f,	
			0.f, 0.f,	
			1.f, 0.f,
			1.f, 1.f,
			// Left wall
			0.f, 1.f,	
			1.f, 1.f,	
			1.f, 0.f,
			0.f, 0.f,	
			// Back loft
			0.f, 0.f, 
			0.5f, 0.5f,
			1.f, 0.f,
			// Left side roof
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			// Rigth side roof
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,	
		};
		// Two textures : roof and walls
		m_Textures.push_back(std::make_pair(wallTextureID, 21));
		m_Textures.push_back(std::make_pair(roofTextureID, 12));
	}
	if (load)
		Load();
}

Hut::~Hut()
{
}
