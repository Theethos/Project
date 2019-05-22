#pragma once

class TextureManager
{
public:

	static void Create();
	static void Destroy();

	static inline unsigned & GetTexture(const std::string & key) { return TextureID.at(key); }
	static bool LoadFromFile(const char * texturePath, const std::string & key);
	static bool DeleteTexture(const std::string & key);

private:
	static std::map<std::string, unsigned> TextureID;
	static bool IsIntantiate;

	static unsigned GetTextureFormat(SDL_Surface * texture, unsigned internalFormat);
	static unsigned GetTextureInternalFormat(SDL_Surface * texture);
	static SDL_Surface * InvertPixels(SDL_Surface * texture);

	TextureManager() = delete;
	~TextureManager() = delete;
};

