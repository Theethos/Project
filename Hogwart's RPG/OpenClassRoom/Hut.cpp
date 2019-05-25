#include "pch.h"
#include "Hut.h"


Hut::Hut(const char * vertexShader, const char * fragmentShader, const unsigned & wallTextureID, const unsigned & roofTextureID, const bool & textured, const bool & load) :
Drawable(vertexShader, fragmentShader)
{
	m_Vertices = std::vector<float>
	{
		// Right wall
		5.f,  0.f,  5.f,	 5.f,  5.f,  5.f,	 5.f,  5.f, -5.f,
		5.f,  0.f,  5.f,	 5.f,  0.f, -5.f,	 5.f,  5.f, -5.f,
		// Back wall
		5.f,  5.f, -5.f,	 5.f,  0.f, -5.f,	-5.f,  0.f, -5.f,
		5.f,  5.f, -5.f,	-5.f,  5.f, -5.f,	-5.f,  0.f, -5.f,
		// Left wall
		-5.f,  5.f, -5.f,	-5.f,  5.f,  5.f,	-5.f,  0.f,  5.f,
		-5.f,  5.f, -5.f,	-5.f,  0.f, -5.f,	-5.f,  0.f,  5.f,
		// Back loft (les combles)
		-5.f,  5.f, -5.f,	 0.f,  6.f,  -5.f,	 5.f,  5.f, -5.f,
		// Left side roof
		-6.f, 4.8f, -6.f,	 0.f,  6.f, -6.f,	 0.f,  6.f,  6.f, 
		-6.f, 4.8f, -6.f,	-6.f, 4.8f,  6.f,	 0.f,  6.f,  6.f,
		// Right side roof
		 0.f,  6.f, -6.f,	 6.f, 4.8f, -6.f,	 6.f, 4.8f,  6.f,
		 0.f,  6.f, -6.f,	 0.f,  6.f,  6.f,	 6.f, 4.8f,  6.f,
	};

	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Right wall
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			// Back wall
			0.f, 1.f,	0.f, 0.f,	1.f, 0.f,
			0.f, 1.f,	1.f, 1.f,	1.f, 0.f,
			// Left wall
			0.f, 1.f,	1.f, 1.f,	1.f, 0.f,
			0.f, 1.f,	0.f, 0.f,	1.f, 0.f,
			// Back loft
			0.f, 0.f,  0.5f, 0.5f,  1.f, 0.f,
			// Left side roof
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			// Rigth side roof
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f
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
		5.f,  0.f,  5.f,	 5.f,  5.f,  5.f,	 5.f,  5.f, -5.f,
		5.f,  0.f,  5.f,	 5.f,  0.f, -5.f,	 5.f,  5.f, -5.f,
		// Back wall
		5.f,  5.f, -5.f,	 5.f,  0.f, -5.f,	-5.f,  0.f, -5.f,
		5.f,  5.f, -5.f,	-5.f,  5.f, -5.f,	-5.f,  0.f, -5.f,
		// Left wall
		-5.f,  5.f, -5.f,	-5.f,  5.f,  5.f,	-5.f,  0.f,  5.f,
		-5.f,  5.f, -5.f,	-5.f,  0.f, -5.f,	-5.f,  0.f,  5.f,
		// Back loft (les combles)
		-5.f,  5.f, -5.f,	 0.f,  6.f,  -5.f,	 5.f,  5.f, -5.f,
		// Left side roof
		-6.f, 4.8f, -6.f,	 0.f,  6.f, -6.f,	 0.f,  6.f,  6.f,
		-6.f, 4.8f, -6.f,	-6.f, 4.8f,  6.f,	 0.f,  6.f,  6.f,
		// Right side roof
		 0.f,  6.f, -6.f,	 6.f, 4.8f, -6.f,	 6.f, 4.8f,  6.f,
		 0.f,  6.f, -6.f,	 0.f,  6.f,  6.f,	 6.f, 4.8f,  6.f
	};

	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Right wall
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			// Back wall
			0.f, 1.f,	0.f, 0.f,	1.f, 0.f,
			0.f, 1.f,	1.f, 1.f,	1.f, 0.f,
			// Left wall
			0.f, 1.f,	1.f, 1.f,	1.f, 0.f,
			0.f, 1.f,	0.f, 0.f,	1.f, 0.f,
			// Back loft
			0.f, 0.f,  0.5f, 0.5f,  1.f, 0.f,
			// Left side roof
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			// Rigth side roof
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
		};
		// Two textures : roof and walls
		m_Textures.push_back(std::make_pair(wallTextureID, 21 * 3));
		m_Textures.push_back(std::make_pair(roofTextureID, 12 * 3));
	}
	if (load)
		Load();
}

Hut::~Hut()
{
}
