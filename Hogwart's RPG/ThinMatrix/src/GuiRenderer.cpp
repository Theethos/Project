#include "pch.h"
#include "GuiRenderer.h"

GuiRenderer::GuiRenderer(Loader & loader) :
	m_Model(loader.LoadToVAO({ -1, 1, -1, -1, 1, 1, 1, -1 }, 2)),
	m_Shader("GuiShader")
{
}

GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::RenderGuis(std::vector<GuiTexture> textures)
{
	m_Shader.Bind();
	glBindVertexArray(m_Model.GetVaoID());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture texture : textures)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
		glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(texture.GetPosition(), texture.GetScale());
		m_Shader.LoadMatrix("transformationMatrix", transformationMatrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Model.GetVertexCount());
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	m_Shader.Unbind();
}
