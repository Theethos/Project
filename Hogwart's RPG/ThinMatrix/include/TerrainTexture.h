#pragma once

class TerrainTexture
{
public:
	TerrainTexture(const unsigned int & textureID);
	~TerrainTexture();

	inline const unsigned int GetTextureID() const { return m_TextureID; }

private:
	unsigned int m_TextureID;
};

