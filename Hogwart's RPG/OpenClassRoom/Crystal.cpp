#include "pch.h"
#include "Crystal.h"

Crystal::Crystal(const char * vertexShader, const char * fragmentShader, const unsigned & textureID, const bool & textured, const bool & load) :
Drawable(vertexShader, fragmentShader),
m_RotationAngle(0.f)
{
	m_Vertices = std::vector<float>
	{
		// Top pyramid
		0.5f, 0.f,  0.5f,   0.5f, 0.f, -0.5f,   0.f,  1.f, 0.f, // Left face
		0.5f, 0.f, -0.5f,  -0.5f, 0.f, -0.5f,   0.f,  1.f, 0.f, // Back face
	   -0.5f, 0.f, -0.5f,  -0.5f, 0.f,  0.5f,   0.f,  1.f, 0.f, // Right face
	   -0.5f, 0.f,  0.5f,   0.5f, 0.f,  0.5f,   0.f,  1.f, 0.f, // Front face
		// Bottom pyramid
		0.5f, 0.f,  0.5f,   0.5f, 0.f, -0.5f,   0.f, -1.f, 0.f, // Left face
		0.5f, 0.f, -0.5f,  -0.5f, 0.f, -0.5f,   0.f, -1.f, 0.f, // Back face
	   -0.5f, 0.f, -0.5f,  -0.5f, 0.f,  0.5f,   0.f, -1.f, 0.f, // Right face
	   -0.5f, 0.f,  0.5f,   0.5f, 0.f,  0.5f,   0.f, -1.f, 0.f, // Front face
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Top pyramid
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			// Bottom pyramid
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(TextureManager::GetTexture("crystalTexture"), m_Vertices.size()));
	}
	if (load)
		Load();
}

Crystal::Crystal(Shader & shader, const unsigned & textureID, const bool & textured, const bool & load) :
Drawable(shader),
m_RotationAngle(0.f)
{
	m_Vertices = std::vector<float>
	{
		// Top pyramid
		0.5f, 0.f,  0.5f,   0.5f, 0.f, -0.5f,   0.f,  1.f, 0.f, // Left face
		0.5f, 0.f, -0.5f,  -0.5f, 0.f, -0.5f,   0.f,  1.f, 0.f, // Back face
	   -0.5f, 0.f, -0.5f,  -0.5f, 0.f,  0.5f,   0.f,  1.f, 0.f, // Right face
	   -0.5f, 0.f,  0.5f,   0.5f, 0.f,  0.5f,   0.f,  1.f, 0.f, // Front face
	    // Bottom pyramid
		0.5f, 0.f,  0.5f,   0.5f, 0.f, -0.5f,   0.f, -1.f, 0.f, // Left face
		0.5f, 0.f, -0.5f,  -0.5f, 0.f, -0.5f,   0.f, -1.f, 0.f, // Back face
	   -0.5f, 0.f, -0.5f,  -0.5f, 0.f,  0.5f,   0.f, -1.f, 0.f, // Right face
	   -0.5f, 0.f,  0.5f,   0.5f, 0.f,  0.5f,   0.f, -1.f, 0.f, // Front face
	};
	m_Textured = textured;
	if (m_Textured)
	{
		m_TextureCoordinates = std::vector<float>
		{
			// Top pyramid
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			// Bottom pyramid
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
			0.f, 0.f,   0.5f, 0.5f,   1.f, 0.f,
		};
		// One texture for all the vertices
		m_Textures.push_back(std::make_pair(TextureManager::GetTexture("crystalTexture"), m_Vertices.size()));
	}
	if (load)
		Load();
}

Crystal::~Crystal()
{
}

void Crystal::Animate()
{
	m_RotationAngle > 360.f ? m_RotationAngle -= 360.f : m_RotationAngle += 0.01f;

	DisplayManager::ModelView = glm::rotate(DisplayManager::ModelView, m_RotationAngle, glm::vec3(0, 1, 0));
}
