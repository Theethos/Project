#include "pch.h"
#include "Crate.h"

Crate::Crate(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured, const bool & load) :
Cube(size, vertexShader, fragmentShader, false)
{
	m_Textured = textured;
	if (m_Textured)
	{
		/*m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
		};*/
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Indices.size()));
	}
	if (load)
		Load();
}

Crate::Crate(const float & size, Shader & shader, const unsigned & textureID, const bool & textured, const bool & load) :
Cube(size, shader, false)
{
	m_Textured = textured;
	if (m_Textured)
	{
		/*m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

			0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
			0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
		};*/
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Indices.size()));
	}
	if (load)
		Load();
}

Crate::~Crate()
{}

