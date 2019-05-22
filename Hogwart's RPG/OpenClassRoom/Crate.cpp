#include "pch.h"
#include "Crate.h"

Crate::Crate(const float & size, const char * vertexShader, const char * fragmentShader, unsigned & texture) :
Cube(size, vertexShader, fragmentShader),
m_Texture(texture),
m_TextureCoordinates
{
	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
}
{}

Crate::Crate(const float & size, Shader & shader, unsigned & texture) :
Cube(size, shader),
m_Texture(texture),
m_TextureCoordinates
{
	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
	0.f, 0.f,	0.f, 1.f,	1.f, 1.f,
}
{}

Crate::~Crate()
{}

void Crate::Draw()
{
	m_Shader.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_Vertices.data());
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_TextureCoordinates.data());
	glEnableVertexAttribArray(2);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(DisplayManager::Projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetID(), "modelview"), 1, GL_FALSE, glm::value_ptr(DisplayManager::ModelView));

	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size() / 3);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);

	m_Shader.Unbind();
}
