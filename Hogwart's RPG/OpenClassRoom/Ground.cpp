#include "pch.h"
#include "Ground.h"

////////////////////////
/// GrassGround
////////////////////////
GrassGround::GrassGround(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured, const bool & load) :
	Drawable(vertexShader, fragmentShader)
{
	m_Vertices = std::vector<float>
	{
		-size / 2, 0.f,  size / 2,   -size / 2, 0.f, -size / 2,	  size / 2, 0.f, -size / 2,
		-size / 2, 0.f,  size / 2,    size / 2, 0.f,  size / 2,   size / 2, 0.f, -size / 2
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	0.f, size,	size, size,
			0.f, 0.f,  size,  0.f,	size, size,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

GrassGround::GrassGround(const float & size, Shader & shader, const unsigned & textureID, const bool & textured, const bool & load) :
	Drawable(shader)
{
	m_Vertices = std::vector<float>
	{
		-size / 2, 0.f,  size / 2,   -size / 2, 0.f, -size / 2,	  size / 2, 0.f, -size / 2,
		-size / 2, 0.f,  size / 2,    size / 2, 0.f,  size / 2,   size / 2, 0.f, -size / 2
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	0.f, size,	size, size,
			0.f, 0.f,  size,  0.f,	size, size,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

GrassGround::~GrassGround()
{
}

////////////////////////
/// DirtGround
////////////////////////
DirtGround::DirtGround(const float & size, const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured, const bool & load) :
Drawable(vertexShader, fragmentShader)	
{
	m_Vertices = std::vector<float>
	{
		-size / 2, 0.f,  size / 2,   -size / 2, 0.f, -size / 2,	  size / 2, 0.f, -size / 2,
		-size / 2, 0.f,  size / 2,    size / 2, 0.f,  size / 2,   size / 2, 0.f, -size / 2
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	0.f, size,	size, size,
			0.f, 0.f,   size, 0.f,	size, size,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

DirtGround::DirtGround(const float & size, Shader & shader, const unsigned & textureID, const bool & textured, const bool & load) :
Drawable(shader)
{
	m_Vertices = std::vector<float>
	{
		-size / 2, 0.f,  size / 2,   -size / 2, 0.f, -size / 2,	  size / 2, 0.f, -size / 2,
		-size / 2, 0.f,  size / 2,    size / 2, 0.f,  size / 2,   size / 2, 0.f, -size / 2
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			0.f, 0.f,	0.f, size,	size, size,
			0.f, 0.f,   size, 0.f,	size, size,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(textureID, m_Vertices.size()));
	}
	if (load)
		Load();
}

DirtGround::~DirtGround()
{
}
