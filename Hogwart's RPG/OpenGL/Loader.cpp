#include "Precompiled_Header_OpenGL.h"
#include "Loader.h"
#include "DisplayManager.h"

Loader::Loader() {}

Loader::~Loader() {}

RawModel Loader::LoadToVAO(std::vector<float> & positions, std::vector<unsigned> & indices, std::vector<float> & textureCoord)
{
	unsigned vao_ID = CreateVAO();
	BindIndicesBuffer(indices);
	StoreDataInAttributeList(0, 3, positions);
	StoreDataInAttributeList(1, 2, textureCoord);
	Unbind();

	return RawModel(vao_ID, indices.size());
}

/*unsigned Loader::LoadTexture(const std::string & filePath)
{
	unsigned texture_id;

	SDL_Surface * texture = IMG_Load(filePath.c_str());
	if (!texture)
	{
		std::cerr << "Can't load the texture '" << filePath << "'. Error in file " << __FILE__ << " line " << __LINE__ << std::endl;
		throw std::exception("Can't load texture");
	}
	m_TextureIDs.push_back(&texture_id);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Get the texture formats (if it supports alpha or not)
	GLenum internal_format = GetTextureInternalFormat(texture);
	GLenum format = GetTextureFormat(texture, internal_format);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texture->w, texture->h, 0, format, GL_UNSIGNED_INT, texture->userdata);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(texture);

	return texture_id;
}*/

void Loader::CleanUp()
{
	for (auto &it : m_VAOInstances)
		glDeleteVertexArrays(1, it);
	for (auto &it : m_VBOInstances)
		glDeleteBuffers(1, it);
	for (auto &it : m_TextureIDs)
		glDeleteTextures(1, it);
}

unsigned Loader::CreateVAO()
{
	unsigned vao_ID;
	glGenVertexArrays(1, &vao_ID);
	m_VAOInstances.push_back(&vao_ID);
	glBindVertexArray(vao_ID);

	return vao_ID;
}

void Loader::BindIndicesBuffer(std::vector<unsigned> & indices)
{
	unsigned vbo_ID;
	glGenBuffers(1, &vbo_ID);
	m_VBOInstances.push_back(&vbo_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
}

void Loader::StoreDataInAttributeList(unsigned attributeNumber, unsigned coordSize, std::vector<float> & data)
{
	unsigned vbo_ID;
	glGenBuffers(1, &vbo_ID);
	m_VBOInstances.push_back(&vbo_ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attributeNumber, coordSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::Unbind()
{
	glBindVertexArray(0);
}

/*GLenum Loader::GetTextureInternalFormat(SDL_Surface * texture)
{
	GLenum internal_format(0);
	if (texture->format->BytesPerPixel == 3)
		internal_format = GL_RGB;
	else if (texture->format->BytesPerPixel == 4)
		internal_format = GL_RGBA;
	else
		throw std::exception("Texture's format is not supported\n");
	return internal_format;
}

GLenum Loader::GetTextureFormat(SDL_Surface * texture, const GLenum & internal_format)
{
	GLenum format(0);
	if (internal_format == GL_RGB)
	{
		if (texture->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}
	else if (internal_format == GL_RGBA)
	{
		if (texture->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}
	return format;
}*/

