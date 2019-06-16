#pragma once

class WaterFrameBuffer
{
public:
	WaterFrameBuffer();
	~WaterFrameBuffer();

	inline void					BindRefractionFrameBuffer() const { BindFrameBuffer(m_RefractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT); }
	inline void					BindReflectionFrameBuffer() const { BindFrameBuffer(m_ReflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT); }
	inline void					UnbindFrameBuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); glViewport(0, 0, DisplayManager::GetWidth(), DisplayManager::GetHeight()); }
	inline const unsigned int & GetReflectionTexture() const { return m_ReflectionTexture; }
	inline const unsigned int & GetRefractionTexture() const { return m_RefractionTexture; }
	inline const unsigned int & GetRefractionDepthTexture() const { return m_RefractionDepthTexture; }


private:
	static unsigned int REFLECTION_WIDTH;
	static unsigned int REFLECTION_HEIGHT;
	
	unsigned int m_ReflectionFrameBuffer;
	unsigned int m_ReflectionTexture;
	unsigned int m_ReflectionDepthBuffer;

	static unsigned int REFRACTION_WIDTH;
	static unsigned int REFRACTION_HEIGHT;

	unsigned int m_RefractionFrameBuffer;
	unsigned int m_RefractionTexture;
	unsigned int m_RefractionDepthTexture;

	void		 InitializeRefractionFrameBuffer();
	void		 InitializeReflectionFrameBuffer();
	inline void	 BindFrameBuffer(const unsigned int & frameBuffer, const unsigned int & width, const unsigned int & height) const { glBindTexture(GL_TEXTURE_2D, 0); glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glViewport(0, 0, width, height); }
	unsigned int CreateFrameBuffer();
	unsigned int CreateTextureAttachment(const unsigned int & width, const unsigned int & height);
	unsigned int CreateDepthBufferAttachment(const unsigned int & width, const unsigned int & height);
	unsigned int CreateDepthTextureAttachment(const unsigned int & width, const unsigned int & height);
};

