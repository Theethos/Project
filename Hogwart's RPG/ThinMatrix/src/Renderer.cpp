#include "pch.h"
#include "Renderer.h"

unsigned int Renderer::NUMBER_LIGHT = 4;

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::RenderEntity(const Entity * entity, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane)
{
	shader.Bind();
	shader.LoadVector4("plane", plane);
	shader.LoadLights(light);
	shader.LoadMatrix("viewMatrix", Maths::CreateViewMatrix(camera));
	shader.LoadVector3("skyColor", DisplayManager::GetFogColor());
	const TexturedModel & texModel = entity->GetTexturedModel();
	const RawModel & model = texModel.GetRawModel();
	const ModelTexture & modelTex = texModel.GetModelTexture();
	
	if (modelTex.GetTransparency())
		glDisable(GL_CULL_FACE);
	else
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	glBindVertexArray(model.GetVaoID());

	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());

	shader.LoadMatrix("transformationMatrix", transformationMatrix);
	shader.LoadShineVariable(modelTex.GetShininess(), modelTex.GetReflectivity());
	shader.LoadBool("useFakeLight", modelTex.GetFakeLight());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modelTex.GetID());
	shader.LoadNumberOfRows(modelTex.GetNumberOfRows());
	shader.LoadOffset({ entity->GetTextureXOffset(), entity->GetTextureYOffset() });

	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	shader.Unbind();
}

void Renderer::RenderEntities(const std::map<TexturedModel, std::vector<Entity *>> & entities, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane)
{
	shader.Bind();
	shader.LoadVector4("plane", plane);
	shader.LoadLights(light);
	shader.LoadMatrix("viewMatrix", Maths::CreateViewMatrix(camera));
	shader.LoadVector3("skyColor", DisplayManager::GetFogColor());

	for (auto & pair : entities)
	{
		const TexturedModel & texModel = pair.first;
		const RawModel & model = texModel.GetRawModel();
		const ModelTexture & modelTex = texModel.GetModelTexture();

		if (modelTex.GetTransparency())
			glDisable(GL_CULL_FACE);
		else
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		glBindVertexArray(model.GetVaoID());

		shader.LoadShineVariable(modelTex.GetShininess(), modelTex.GetReflectivity());
		shader.LoadBool("useFakeLight", modelTex.GetFakeLight());
		shader.LoadNumberOfRows(modelTex.GetNumberOfRows());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, modelTex.GetID());

		for (const Entity * entity : pair.second)
		{
			shader.LoadOffset({ entity->GetTextureXOffset(), entity->GetTextureYOffset() });
			glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
			shader.LoadMatrix("transformationMatrix", transformationMatrix);
			glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
	shader.Unbind();
}

void Renderer::RenderTerrains(const std::vector<Terrain> & terrains, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane)
{
	shader.Bind();
	shader.LoadVector4("plane", plane);
	shader.LoadLights(light);
	shader.LoadMatrix("viewMatrix", Maths::CreateViewMatrix(camera));
	shader.LoadVector3("skyColor", DisplayManager::GetFogColor());
	for (const Terrain & terrain : terrains)
	{
		const RawModel & model = terrain.GetRawModel();
		const TerrainTexturePack & texPack = terrain.GetTextures();

		glBindVertexArray(model.GetVaoID());

		glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix({ terrain.GetGridX(), 0.f, terrain.GetGridZ() }, { 0, 0, 0 }, 1.f);

		shader.LoadMatrix("transformationMatrix", transformationMatrix);
		shader.LoadShineVariable(1, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texPack.GetBackground().GetTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texPack.GetRColor().GetTextureID());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texPack.GetGColor().GetTextureID());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texPack.GetBColor().GetTextureID());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, terrain.GetBlendMap().GetTextureID());

		shader.ConnectTextureUnits();

		glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
	shader.Unbind();
}
