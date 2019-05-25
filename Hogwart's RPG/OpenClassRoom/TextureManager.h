#pragma once

#define LoadTex TextureManager::LoadFromFile
#define LoadEmptyTex TextureManager::LoadEmptyTexture
#define GetTex TextureManager::GetTexture

class TextureManager
{
public:

	static void Create();
	static void Destroy();

	static unsigned & GetTexture(const std::string & key);
	static unsigned LoadFromFile(const char * texturePath, const std::string & key);
	static unsigned LoadEmptyTexture(const unsigned & w, const unsigned & h,
								 const unsigned & format,const unsigned & internalFormat);
	static bool DeleteTexture(const std::string & key);

private:
	static std::map<std::string, unsigned> TextureID;
	static std::vector<unsigned> EmptyTextureID;
	static bool IsIntantiate;

	static unsigned GetTextureFormat(SDL_Surface * texture, unsigned internalFormat);
	static unsigned GetTextureInternalFormat(SDL_Surface * texture);
	static SDL_Surface * InvertPixels(SDL_Surface * texture);

	TextureManager() = delete;
	~TextureManager() = delete;
};

