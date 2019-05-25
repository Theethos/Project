#pragma once

#include "Shader.h"


class Drawable
{
public:
	virtual void Draw(const glm::mat4 & modelview = MV, const glm::mat4 & projection = DisplayManager::Projection);
	virtual bool SetTexture(const unsigned & currentTextureID, const unsigned & newTextureId);
	virtual void UpdateVBOData(void * data, const unsigned & sizeOf, const int & offset);
protected:
	Drawable(const char * vertexShader, const char * fragmentShader);
	Drawable(Shader & shader);
	virtual ~Drawable();
	virtual void Load();

	unsigned m_DrawType;
	unsigned m_SizeOfVertices, m_SizeOfColors, m_SizeOfTextureCoordinates;
	unsigned m_SizeOfVerticesIndices, m_SizeOfColorsIndices, m_SizeOfTextureCoordinatesIndices;
	unsigned m_VboID, m_VaoID, m_IndexBufferID;
	bool m_Textured;
	Shader m_Shader;
	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;
	std::vector<float> m_TextureCoordinates;
	std::vector<unsigned short> m_VerticesIndices;
	std::vector<unsigned short> m_ColorsIndices;
	std::vector<unsigned short> m_TextureCoordinatesIndices;
	std::vector<std::pair<unsigned, unsigned>> m_Textures;	// Pair of textureID & numberOfVerticesAffectedWithThatTexture
};
