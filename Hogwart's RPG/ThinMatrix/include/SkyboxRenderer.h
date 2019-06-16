#pragma once

#include "Loader.h"
#include "Shader.h"

class SkyboxRenderer
{
public:
	SkyboxRenderer(Loader & loader);
	~SkyboxRenderer();

	void RenderSkybox(Camera & camera);

	inline const float & GetRotation() const { return m_Rotation; }

private:
	void BindTexturesTime();

	static float SIZE, ROTATION_SPEED;
	static std::vector<std::string> DAY_PATHS, NIGHT_PATHS;
	static std::vector<float> POSITIONS;
	RawModel m_Model;
	unsigned int m_DayTextureID, m_NightTextureID;
	Shader m_Shader;
	float m_Rotation;
};

