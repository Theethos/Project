#include "pch.h"
#include "Texture.h"


Texture::Texture() :
m_TextureID(0)
{}


Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

bool Texture::LoadFromFile(const char * texturePath)
{
	SDL_Surface * texture = IMG_Load(texturePath);
	if (!texture)
	{
		std::cerr << "Can't load the file '" << texturePath << "'.\n";
		return false;
	}
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	unsigned internal_format = GetTextureInternalFormat(texture);
	unsigned format = GetTextureFormat(texture, internal_format);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(texture);
	return true;
}

unsigned Texture::GetTextureFormat(SDL_Surface * texture, unsigned internalFormat)
{
	if (internalFormat == GL_RGBA)
	{
		if (texture->format->Rmask == 0xff)
		{
			return GL_RGBA;
		}
		else
		{
			return GL_BGRA;
		}
	}
	else if (internalFormat == GL_RGB)
	{
		if (texture->format->Rmask == 0xff)
		{
			return GL_RGB;
		}
		else
		{
			return GL_BGR;
		}
	}
}

unsigned Texture::GetTextureInternalFormat(SDL_Surface * texture)
{
	if (texture->format->BytesPerPixel == 3)
	{
		return GL_RGB;
	}
	else if (texture->format->BytesPerPixel == 4)
	{
		return GL_RGBA;
	}
	else
	{
		std::cerr << "Unknow image format\n";
		return 0;
	}
}
