#pragma once

class ModelTexture
{
public:
	ModelTexture(const unsigned & textureID);
	~ModelTexture();

	inline const unsigned GetID() const { return m_TextureID; }

private:
	unsigned m_TextureID;
};

