#pragma once

#include "Shader.h"
#include "WaterTile.h"
#include "WaterFrameBuffer.h"

class WaterRenderer
{
public:
	WaterRenderer(Loader & loader, WaterFrameBuffer & fbos);
	~WaterRenderer();

	void Render(std::vector<WaterTile> & waters, Camera & camera, const std::vector<Light> & light);

private:
	static std::string DUDV_MAP, NORMAL_MAP;
	static float WAVE_SPEED;
	unsigned int m_DudvMapID, m_NormalMapID;
	RawModel m_Model;
	Shader m_Shader;
	WaterFrameBuffer & m_Fbos;
	float m_MoveFactor;
};

