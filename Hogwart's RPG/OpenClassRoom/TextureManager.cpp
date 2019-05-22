#include "pch.h"

std::map<std::string, unsigned> TextureManager::TextureID;
bool TextureManager::IsIntantiate(false);

void TextureManager::Create()
{
	if (!IsIntantiate)
		IsIntantiate = true;
	else
	{
		std::cerr << "A TextureManagerManager as already been created\n";
	}
}

void TextureManager::Destroy()
{
	if (IsIntantiate)
	{
		for (auto & it : TextureID)
			glDeleteTextures(1, &(it.second));
		IsIntantiate = false;
	}
}

bool TextureManager::LoadFromFile(const char * texturePath, const std::string & key)
{
	if (IsIntantiate && !TextureID.count(key))
	{
		SDL_Surface * texture = IMG_Load(texturePath);
		if (!texture)
		{
			std::cerr << "Can't load the file '" << texturePath << "'.\n";
			return false;
		}

		texture = InvertPixels(texture);

		unsigned texture_id(0);

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		unsigned internal_format = GetTextureInternalFormat(texture);
		unsigned format = GetTextureFormat(texture, internal_format);

		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

		SDL_FreeSurface(texture);
		// Add the texture to the map
		TextureID[key] = texture_id;
		return true;
	}
	else if (TextureID.count(key))
		std::cerr << "Texture already created\n";
	return false;
}

bool TextureManager::DeleteTexture(const std::string & key)
{
	if (IsIntantiate)
		glDeleteTextures(1, &(TextureID[key]));
}

unsigned TextureManager::GetTextureFormat(SDL_Surface * texture, unsigned internalFormat)
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

unsigned TextureManager::GetTextureInternalFormat(SDL_Surface * texture)
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

// This function inverts the coordinates of a texture, because SDL axes' origin is not the same as OpenGL's axes' origin
SDL_Surface * TextureManager::InvertPixels(SDL_Surface * texture)
{
	SDL_Surface * invert_texture = SDL_CreateRGBSurface(0, texture->w, texture->h, texture->format->BitsPerPixel,
				texture->format->Rmask, texture->format->Gmask, texture->format->Bmask, texture->format->Amask);
	unsigned char * texture_pixels			= static_cast<unsigned char *>(texture->pixels);
	unsigned char * invert_texture_pixels	= static_cast<unsigned char *>(invert_texture->pixels);
	
	for (unsigned i = 0; i < texture->h; ++i)
	{
		for (unsigned j = 0; j < texture->w * texture->format->BytesPerPixel; ++j)
		{
			invert_texture_pixels[(texture->w * texture->format->BytesPerPixel * (texture->h - 1 - i)) + j] = texture_pixels[(texture->w * texture->format->BytesPerPixel * i) + j];
		}
	}

	return invert_texture;
}
