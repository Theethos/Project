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
	
	StoreDataInAttributeList(0, 3, vertices);
	StoreDataInAttributeList(1, 2, textureCoords);
	StoreDataInAttributeList(2, 3, normals);
	
	BindIndicesBuffer(indices);

	glBindVertexArray(0);

	return RawModel(vao_id, indices.size());
}

unsigned Loader::LoadTexture(const char * texturePath, const bool & flip)
{
	stbi_set_flip_vertically_on_load(flip);
	int width, height, channels;
	unsigned int format = 4;
	unsigned char *data = stbi_load(texturePath, &width, &height, &channels, 0);
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);


	if (data)
	{
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4);
	}
	else
	{
		std::cerr << "Failed to load the texture\n";
	}
	stbi_image_free(data);
	m_Textures.push_back(texture_id);
	//glBindTexture(GL_TEXTURE_2D, 0);
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
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, dimension, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributeNumber);

	m_Vbos.push_back(vbo_id);
}

void Loader::BindIndicesBuffer(const std::vector<unsigned int> & indices)
{
	// Create a new vbo to stroe the indices
	unsigned vbo_id;

	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	m_Vbos.push_back(vbo_id);
}