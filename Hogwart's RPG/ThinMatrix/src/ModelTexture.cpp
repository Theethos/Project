#include "pch.h"
#include "ModelTexture.h"

ModelTexture::ModelTexture(const unsigned & textureID, const float & shininess, const float & reflectivity) :
	m_TextureID(textureID),
	m_Shininess(shininess),
	m_Reflectivity(reflectivity),
	m_HasTransparency(false),
	m_HasFakeLight(false),
	m_NumberOfRows(1)
{
}

ModelTexture::~ModelTexture()
{
}
