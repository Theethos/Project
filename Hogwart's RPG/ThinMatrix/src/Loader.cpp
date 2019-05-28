#include "pch.h"
#include "Loader.h"

Loader::Loader() 
{}

Loader::~Loader()
{
	// Delete the vaos and vbos
	for (auto & it : m_Vaos)
		glDeleteVertexArrays(1, &it);
	for (auto & it : m_Vbos)
		glDeleteBuffers(1, &it);
	for (auto & it : m_Textures)
		glDeleteTextures(1, &it);
}

RawModel Loader::LoadToVAO(const std::vector<float>& vertices, const std::vector<float> & textureCoords,
						   const std::vector<float> & normals, const std::vector<unsigned int> & indices)
{
	// Load the data in a VAO
	unsigned vao_id = CreateVAO();
	BindIndicesBuffer(indices);
	
	StoreDataInAttributeList(0, 3, vertices);
	StoreDataInAttributeList(1, 2, textureCoords);
	StoreDataInAttributeList(2, 3, normals);

	glBindVertexArray(0);

	return RawModel(vao_id, indices.size());
}

unsigned Loader::LoadTexture(const std::string & texturePath)
{
	SDL_Surface * texture = IMG_Load(texturePath.c_str());
	if (!texture)
	{
		std::cerr << "Can't load the file '" << texturePath << "'.\n";
		return 0;
	}

	texture = InvertPixels(texture);

	unsigned texture_id(0);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	unsigned internal_format = GetTextureInternalFormat(texture);
	unsigned format = GetTextureFormat(texture, internal_format);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(texture);
	// Add the texture to the map
	return texture_id;
}

unsigned Loader::CreateVAO()
{
	// Create a vao to store data
	unsigned vao_id;

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	m_Vaos.push_back(vao_id);

	return vao_id;
}

void Loader::StoreDataInAttributeList(const unsigned & attributeNumber, const unsigned & dimension, const std::vector<float> & data)
{
	// Create a vbo to store the data and then put it in a vao
	unsigned vbo_id;

	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), data.data());	
	glVertexAttribPointer(attributeNumber, dimension, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_Vbos.push_back(vbo_id);
}

void Loader::BindIndicesBuffer(const std::vector<unsigned int> & indices)
{
	// Create a new vbo to stroe the indices
	unsigned vbo_id;

	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

	m_Vbos.push_back(vbo_id);
}

unsigned Loader::GetTextureFormat(SDL_Surface * texture, unsigned internalFormat)
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

unsigned Loader::GetTextureInternalFormat(SDL_Surface * texture)
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
SDL_Surface * Loader::InvertPixels(SDL_Surface * texture)
{
	SDL_Surface * invert_texture = SDL_CreateRGBSurface(0, texture->w, texture->h, texture->format->BitsPerPixel,
		texture->format->Rmask, texture->format->Gmask, texture->format->Bmask, texture->format->Amask);
	unsigned char * texture_pixels = static_cast<unsigned char *>(texture->pixels);
	unsigned char * invert_texture_pixels = static_cast<unsigned char *>(invert_texture->pixels);

	for (unsigned i = 0; i < texture->h; ++i)
	{
		for (unsigned j = 0; j < texture->w * texture->format->BytesPerPixel; ++j)
		{
			invert_texture_pixels[(texture->w * texture->format->BytesPerPixel * (texture->h - 1 - i)) + j] = texture_pixels[(texture->w * texture->format->BytesPerPixel * i) + j];
		}
	}

	return invert_texture;
}