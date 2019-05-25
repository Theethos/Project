#include "pch.h"
#include "Drawable.h"

Drawable::Drawable(const char * vertexShader, const char * fragmentShader) :
m_Shader(vertexShader, fragmentShader),
m_Vertices(1.0),
m_Colors(1.0),
m_TextureCoordinates(1.0),
m_Textures(1.0),
m_Textured(false),
m_DrawType(GL_TRIANGLES),
m_VaoID(0),
m_VboID(0),
m_SizeOfColors(0),
m_SizeOfVertices(0),
m_SizeOfTextureCoordinates(0)
{}

Drawable::Drawable(Shader & shader) : 
m_Shader(shader),
m_Vertices(1.0),
m_Colors(1.0),
m_TextureCoordinates(1.0),
m_Textures(1.0),
m_Textured(false),
m_DrawType(GL_TRIANGLES),
m_VaoID(0),
m_VboID(0),
m_SizeOfColors(0),
m_SizeOfVertices(0),
m_SizeOfTextureCoordinates(0)
{}

Drawable::~Drawable()
{
	glDeleteBuffers(1, &m_VboID);
	glDeleteVertexArrays(1, &m_VaoID);
}

void Drawable::Draw(const glm::mat4 & modelview, const glm::mat4 & projection)
{
	// Bind the shader
	m_Shader.Bind();

	// Bind the vao
	glBindVertexArray(m_VaoID);

	// Send the matrixe
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetID(), "modelviewProjection"), 1, GL_FALSE, value_ptr(projection * modelview));

	if (m_Textured)
	{
		unsigned vertices_count = 0;
		for (auto & it : m_Textures)
		{
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, it.first);

			// Draw
			glDrawArrays(m_DrawType, vertices_count / 3, it.second / 3);
			
			// Unbind the texture and disable the texture data
			glBindTexture(GL_TEXTURE_2D, 0);
			vertices_count += it.second;
		}
	}
	else
		// Draw
		glDrawArrays(m_DrawType, 0, m_Vertices.size() / 3);

	// Disable the vertices data
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbind the shader
	m_Shader.Unbind();
}

bool Drawable::SetTexture(const unsigned & currentTextureID, const unsigned & newTextureId)
{
	if (m_Textured)
	{
		for (auto & it : m_Textures)
		{
			if (currentTextureID == it.first)
			{
				it.first = newTextureId;
				return true;
			}
		}
	}
	return false;
}

void Drawable::Load()
{
	// Set the size the different datas
	m_SizeOfVertices = m_Vertices.size() * sizeof(float);
	if (m_Textured)
		m_SizeOfTextureCoordinates = m_TextureCoordinates.size() * sizeof(float);
	else
		m_SizeOfColors = m_Colors.size() * sizeof(float);

	// Check that the buffer has not already been created
	if (glIsBuffer(m_VboID) == GL_TRUE)
		glDeleteBuffers(1, &m_VboID);

	// Generate the buffers
	glGenBuffers(1, &m_VboID);

	// Bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);

		// Allocate the right amount of memory for all the data
		if (m_Textured)
			glBufferData(GL_ARRAY_BUFFER, m_SizeOfVertices + m_SizeOfTextureCoordinates, 0, GL_STATIC_DRAW);
		else
			glBufferData(GL_ARRAY_BUFFER, m_SizeOfVertices + m_SizeOfColors, 0, GL_STATIC_DRAW);

		// Send the data into the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_SizeOfVertices, m_Vertices.data());

		if (m_Textured)
			glBufferSubData(GL_ARRAY_BUFFER, m_SizeOfVertices, m_SizeOfTextureCoordinates, m_TextureCoordinates.data());
		else
			glBufferSubData(GL_ARRAY_BUFFER, m_SizeOfVertices, m_SizeOfColors, m_Colors.data());
	
	// Unbind the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (glIsVertexArray(m_VaoID))
		glDeleteVertexArrays(1, &m_VaoID);

	// Generate the vertex array object
	glGenVertexArrays(1, &m_VaoID);
	// Bind the vao
	glBindVertexArray(m_VaoID);
		// Bind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
			// Send the vertices
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);

			if (m_Textured)
			{
				// Send the texture
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_SizeOfVertices));
				glEnableVertexAttribArray(2);
			}
			else
			{
				// Send the colors
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_SizeOfVertices));
				glEnableVertexAttribArray(1);
			}
		// Unbind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind the vao
	glBindVertexArray(0);
}

void Drawable::UpdateVBOData(void * data, const unsigned & sizeOf, const int & offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
		void * pVBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (!pVBO)
		{
			std::cerr << "Can't acces to the VBO. Error in '" << __FILE__ << "', line " << __LINE__ << std::endl;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return;
		}
		memcpy((char *)pVBO + offset, data, sizeOf);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		pVBO = nullptr;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
