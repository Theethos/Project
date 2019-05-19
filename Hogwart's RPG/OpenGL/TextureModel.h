#pragma once

#include "RawModel.h"

class TextureModel
{
public:
	TextureModel(RawModel & rawModel);//, sf::Texture * texture);
	~TextureModel();

	inline RawModel &		GetRawModel() { return m_RawModel; }
	//inline sf::Texture *	GetTexture() { return m_Texture; }

private:
	RawModel & m_RawModel;
	//sf::Texture * m_Texture;
};

