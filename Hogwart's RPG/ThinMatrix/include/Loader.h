#pragma once

#include "RawModel.h"
#include "TextureData.h"

class Loader
{
public:
	Loader();
	~Loader();

	RawModel		LoadToVAO(const std::vector<float> & positions, const std::vector<float> & textureCoords,
					   const std::vector<float> & normals, const std::vector<unsigned int> & indices);
	RawModel		LoadToVAO(const std::vector<float> & positions, const unsigned int & dimension);
	unsigned int	LoadTexture(const char * texturePath, const bool & flip = false);
	unsigned int	LoadCubeMap(const std::vector<std::string> & texturePaths);
private:
	// Store the vao and vbo to delete them at the end
	std::vector<unsigned> m_Vaos;
	std::vector<unsigned> m_Vbos;
	std::vector<unsigned> m_Textures;

	unsigned CreateVAO();
	void StoreDataInAttributeList(const unsigned & attributeNumber, const unsigned & dimension, const std::vector<float> & data);
	void BindIndicesBuffer(const std::vector<unsigned int> & indices);

	unsigned GetTextureFormat(SDL_Surface * texture, unsigned internalFormat);
	unsigned GetTextureInternalFormat(SDL_Surface * texture);
	SDL_Surface * InvertPixels(SDL_Surface * texture);
};

