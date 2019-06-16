#pragma once

#include "GuiTexture.h"
#include "Shader.h"

class GuiRenderer
{
public:
	GuiRenderer(Loader & loader);
	~GuiRenderer();

	void RenderGuis(std::vector<GuiTexture> textures);

private:
	RawModel m_Model;
	Shader m_Shader;
};

