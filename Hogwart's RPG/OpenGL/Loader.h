#pragma once
#include "RawModel.h"

class Loader
{
public:
	Loader();
	~Loader();

	RawModel		LoadToVAO(std::vector<float> & positions, std::vector<unsigned> & indices, std::vector<float> & textureCoord);
	unsigned		LoadTexture(const std::string & filePath);
	void			CleanUp();

private:
	unsigned		CreateVAO();
	void			BindIndicesBuffer(std::vector<unsigned> & indices);
	void			StoreDataInAttributeList(unsigned attributeNumber, unsigned coordSize, std::vector<float> & data);
	void			Unbind();
	GLenum			GetTextureFormat(SDL_Surface * texture);
	GLenum			GetTextureInternalFormat(SDL_Surface * texture);
	std::vector<unsigned*>	m_VAOInstances;
	std::vector<unsigned*>	m_VBOInstances;
	std::vector<unsigned*>	m_Textures;
};

