#include "pch.h"
#include "GuiTexture.h"

GuiTexture::GuiTexture(const glm::vec2 & position, const glm::vec2 & scale, const unsigned int & textureID) :
	m_Position(position),
	m_Scale(scale),
	m_Texture(textureID)
{
}

GuiTexture::~GuiTexture()
{
}
