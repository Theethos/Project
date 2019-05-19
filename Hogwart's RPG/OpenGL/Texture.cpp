#include "Precompiled_Header_OpenGL.h"
#include "Texture.h"


Texture::Texture(std::string path) :
m_TextureID(0),
m_Path(path),
m_Texture(nullptr),
m_Width(0), m_Height(0), m_BPP(0)
{
	m_Texture = IMG_Load(path.c_str());
	if (!m_Texture)
	{
		std::cerr << "Can't load the texture '" << path << "'. Error in file " << __FILE__ << " line " << __LINE__ << std::endl;
		throw std::exception("Can't load texture");
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(const unsigned slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
