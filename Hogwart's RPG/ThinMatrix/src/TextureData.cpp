#include "pch.h"
#include "TextureData.h"


TextureData::TextureData(unsigned char * data, const unsigned int & width, const unsigned int & height) :
	m_Data(data),
	m_Width(width),
	m_Height(height)
{
}


TextureData::~TextureData()
{
}
