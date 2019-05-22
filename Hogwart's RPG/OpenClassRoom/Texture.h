#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	inline const unsigned & GetID() const { return m_TextureID; }
	bool LoadFromFile(const char * texturePath);

private:
	unsigned m_TextureID;

	unsigned GetTextureFormat(SDL_Surface * texture, unsigned internalFormat);
	unsigned GetTextureInternalFormat(SDL_Surface * texture);

};

