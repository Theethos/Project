#pragma once

#include "Cube.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(const unsigned & w, const unsigned & h, const float & screenSize = 0, Shader * shader = nullptr, const bool & useStencil = false);
	~FrameBuffer();

	bool Load(const bool & useStencil = false);
	void StartDrawingInto();
	void EndDrawingInto(const unsigned & w_w, const unsigned & w_h, const bool & show = false, const glm::vec4 & clearColor = DisplayManager::GetClearColor());
	inline void PushMatrix() { m_Save = m_ModelView; }
	inline void PopMatrix() { m_ModelView = m_Save; }

	inline const unsigned GetID() const { return m_ID; }
	inline const unsigned GetColorBufferID(const unsigned & index) const { return m_ColorBufferID[index]; }
	inline const unsigned GetWidth() const { return m_Width; }
	inline const unsigned GetHeight() const { return m_Height; }
	inline glm::mat4 GetModelView() { return m_ModelView; }
	inline glm::mat4 GetProjection() { return m_Projection; }
	inline glm::mat4 GetSaveMatrix() { return m_Save; }

	inline void SetModelView(const glm::mat4 & modelView) { m_ModelView = modelView; }
	inline void SetProjection(const glm::mat4 & projection) { m_Projection = projection; }
	inline void SetSaveModelView(const glm::mat4 & saveModelView) { m_Save = saveModelView; }

private:
	glm::mat4 m_ModelView, m_Projection, m_Save;
	unsigned m_ID, m_Width, m_Height;
	std::vector<unsigned> m_ColorBufferID;
	unsigned m_DepthBufferID;
	Square * m_Screen;


	void CreateRenderBuffer(unsigned & id, const unsigned & internalFormat);
};

