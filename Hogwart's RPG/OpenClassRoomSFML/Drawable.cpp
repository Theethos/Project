#include "pch.h"
#include "Drawable.h"

Drawable::Drawable(const std::string & vertexShader, const std::string & fragmentShader) :
m_Shader(vertexShader, fragmentShader),
m_Vertices(1.0),
m_Colors(1.0),
m_DrawType(GL_TRIANGLES)
{}

Drawable::Drawable(Shader & shader) : 
m_Shader(shader),
m_Vertices(1.0),
m_Colors(1.0),
m_DrawType(GL_TRIANGLES)
{}

Drawable::~Drawable(){}

void Drawable::Draw(glm::mat4 & modelView, glm::mat4 projection)
{
	// Bind the shader
	m_Shader.Bind();

	// Send the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_Vertices.data());
	glEnableVertexAttribArray(0);

	// Send the colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_Colors.data());
	glEnableVertexAttribArray(1);

	// Send the matrixes
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));

	// Draw
	glDrawArrays(m_DrawType, 0, m_Vertices.size() / 3);

	// Disable the data
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// Unbind the shader
	m_Shader.Unbind();
}
