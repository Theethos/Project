#include "pch.h"
#include "WaterRenderer.h"

std::string WaterRenderer::DUDV_MAP = "res/dudvmaps/dudvmap_0.png";
std::string WaterRenderer::NORMAL_MAP = "res/normalmaps/normalmap_0.png";
float WaterRenderer::WAVE_SPEED = 0.01f;

WaterRenderer::WaterRenderer(Loader & loader, WaterFrameBuffer & fbos):
	m_Model(loader.LoadToVAO({-1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1}, 2)),
	m_Shader("WaterShader"),
	m_Fbos(fbos),
	m_DudvMapID(loader.LoadTexture(DUDV_MAP.c_str())),
	m_NormalMapID(loader.LoadTexture(NORMAL_MAP.c_str())),
	m_MoveFactor(0)
{
	m_Shader.Bind();
	m_Shader.LoadInt("reflectionTexture", 0);
	m_Shader.LoadInt("refractionTexture", 1);
	m_Shader.LoadInt("dudvMap", 2);
	m_Shader.LoadInt("normalMap", 3);
	m_Shader.LoadInt("depthMap", 4);
	m_Shader.LoadFloat("near", DisplayManager::GetNear());
	m_Shader.LoadFloat("far", DisplayManager::GetFar());
	m_Shader.Unbind();
}

WaterRenderer::~WaterRenderer()
{
}

void WaterRenderer::Render(std::vector<WaterTile> & waters, Camera & camera, const std::vector<Light> & light)
{
	m_Shader.Bind();
	m_Shader.LoadMatrix("viewMatrix", Maths::CreateViewMatrix(camera));
	m_Shader.LoadVector3("cameraPosition", camera.GetPosition());
	m_Shader.LoadLights(light);
	glBindVertexArray(m_Model.GetVaoID());
	m_MoveFactor += WAVE_SPEED * DisplayManager::GetFrameTime();
	m_MoveFactor = std::fmodf(m_MoveFactor, 1.f);
	m_Shader.LoadFloat("moveFactor", m_MoveFactor);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Fbos.GetReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Fbos.GetRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_DudvMapID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_NormalMapID);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_Fbos.GetRefractionDepthTexture());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto tile : waters)
	{
		m_Shader.LoadMatrix("modelMatrix", Maths::CreateTransformationMatrix(glm::vec3(tile.GetX(), tile.GetHeight(), tile.GetZ()), glm::vec3(0, 0, 0), WaterTile::TILE_SIZE));
		glDrawArrays(GL_TRIANGLES, 0, m_Model.GetVertexCount());
	}
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	m_Shader.Unbind();
}
