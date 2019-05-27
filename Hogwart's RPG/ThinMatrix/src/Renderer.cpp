#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(Shader & shader) :
	m_Shader(shader),
	m_Fov(70.0),
	m_AspectRatio((double)DisplayManager::GetWidth() / DisplayManager::GetHeight()),
	m_Near(0.1),
	m_Far(1000.0)
{
	m_ProjectionMatrix = glm::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
	m_Shader.Bind();
	m_Shader.LoadMatrix("projectionMatrix", m_ProjectionMatrix);
	m_Shader.Unbind();
}

Renderer::~Renderer()
{}

void Renderer::Render(const Entity & entity)
{
	TexturedModel texModel = entity.GetTexturedModel();
	RawModel model = texModel.GetRawModel();
	
	glBindVertexArray(model.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());

	m_Shader.LoadMatrix("transformationMatrix", transformationMatrix);

	glBindTexture(GL_TEXTURE_2D, texModel.GetModelTexture().GetID());
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
