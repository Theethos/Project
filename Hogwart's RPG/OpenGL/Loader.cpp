#include "Precompiled_Header_OpenGL.h"
#include "Loader.h"

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

unsigned Loader::LoadTexture(const std::string & filePath)
{
	unsigned texture_id;
	SDL_Surface * texture = IMG_Load(filePath.c_str());
	if (!texture)
	{
		std::cerr << "Can't load the texture '" << filePath << "'. Error in file " << __FILE__ << " line " << __LINE__ << std::endl;
		throw std::exception("Can't load texture");
	}
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_INT, texture->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Loader::CleanUp()
{
	for (auto &it : m_VAOInstances)
		glDeleteVertexArrays(1, it);
	for (auto &it : m_VBOInstances)
		glDeleteBuffers(1, it);
	for (auto &it : m_Textures)
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

GLenum Loader::GetTextureFormat(SDL_Surface * texture)
{
	GLenum format;
	if (texture->format->BytesPerPixel == 3)
		format = GL_RGB;
	else if (texture->format->BytesPerPixel == 3)
		format = GL_RGBA;
	else
		throw std::exception("Texture format not supported\n");
}

GLenum Loader::GetTextureInternalFormat(SDL_Surface * texture)
{
	return GLenum();
}
