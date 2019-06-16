#include "pch.h"
#include "SkyboxRenderer.h"

float SkyboxRenderer::SIZE = 500.f;
float SkyboxRenderer::ROTATION_SPEED = 0.1f;
std::vector<std::string> SkyboxRenderer::DAY_PATHS
{
	"res/textures/skyboxes/Day/right.jpg",
	"res/textures/skyboxes/Day/left.jpg",
	"res/textures/skyboxes/Day/top.jpg",
	"res/textures/skyboxes/Day/bottom.jpg",
	"res/textures/skyboxes/Day/front.jpg",
	"res/textures/skyboxes/Day/back.jpg"
};
std::vector<std::string> SkyboxRenderer::NIGHT_PATHS
{
	"res/textures/skyboxes/Night/right.png",
	"res/textures/skyboxes/Night/left.png",
	"res/textures/skyboxes/Night/top.png",
	"res/textures/skyboxes/Night/bottom.png",
	"res/textures/skyboxes/Night/front.png",
	"res/textures/skyboxes/Night/back.png"
};
std::vector<float> SkyboxRenderer::POSITIONS
{
		-SIZE,  SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		-SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		 SIZE, -SIZE,  SIZE
};

SkyboxRenderer::SkyboxRenderer(Loader & loader) : 
	m_Shader("SkyboxShader"),
	m_Model(loader.LoadToVAO(POSITIONS, 3)),
	m_DayTextureID(loader.LoadCubeMap(DAY_PATHS)),
	m_NightTextureID(loader.LoadCubeMap(NIGHT_PATHS)),
	m_Rotation(0.f)
{
	m_Shader.Bind();
	m_Shader.LoadInt("cubeMap", 0);
	m_Shader.LoadInt("cubeMap2", 1);
	m_Shader.Unbind();
}

SkyboxRenderer::~SkyboxRenderer()
{
}

void SkyboxRenderer::RenderSkybox(Camera & camera)
{
	glDepthMask(GL_FALSE);
	m_Shader.Bind();
	auto viewMatrix = Maths::CreateViewMatrix(camera);
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
	m_Rotation += ROTATION_SPEED * DisplayManager::GetFrameTime();
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_Rotation), { 0, 1, 0 });
	m_Shader.LoadMatrix("viewMatrix", viewMatrix);
	m_Shader.LoadVector3("fogColor", DisplayManager::GetFogColor());
	m_Shader.LoadFloat("blendFactor", DisplayManager::GetBlendFactor());
	glBindVertexArray(m_Model.GetVaoID());
	BindTexturesTime();
	glDrawArrays(GL_TRIANGLES, 0, m_Model.GetVertexCount());
	glBindVertexArray(0);
	m_Shader.Unbind();
	glDepthMask(GL_TRUE);
}

void SkyboxRenderer::BindTexturesTime()
{
	const double & time = DisplayManager::GetTime();
	unsigned int texture1;
	unsigned int texture2;
	if (time >= 0 && time < 230.f)
	{
		texture1 = m_NightTextureID;
		texture2 = m_NightTextureID;
	}
	else if (time >= 230.f && time < 250.f)
	{
		texture1 = m_DayTextureID;
		texture2 = m_NightTextureID;
	}
	else if (time >= 250.f && time < 480.f)
	{
		texture1 = m_DayTextureID;
		texture2 = m_DayTextureID;
	}
	else
	{
		texture1 = m_DayTextureID;
		texture2 = m_NightTextureID;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
}
