#include "Precompiled_Header_OpenGL.h"
#include "Renderer.h"


Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Clear()
{
	glClearColor(1.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(TextureModel & textureModel)
{
	RawModel model = textureModel.GetRawModel();
	glBindVertexArray(model.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	//sf::Texture::bind(textureModel.GetTexture());
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
	//sf::Texture::bind(nullptr);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Renderer::Render(RawModel & rawModel)
{
	glBindVertexArray(rawModel.GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, rawModel.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

