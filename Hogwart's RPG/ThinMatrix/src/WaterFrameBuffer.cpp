#include "pch.h"
#include "WaterFrameBuffer.h"

unsigned int WaterFrameBuffer::REFLECTION_WIDTH = 0;
unsigned int WaterFrameBuffer::REFLECTION_HEIGHT = 0;
unsigned int WaterFrameBuffer::REFRACTION_WIDTH = 0;
unsigned int WaterFrameBuffer::REFRACTION_HEIGHT = 0;

WaterFrameBuffer::WaterFrameBuffer()
{
	REFLECTION_WIDTH = DisplayManager::GetWidth();
	REFLECTION_HEIGHT = DisplayManager::GetHeight();
	REFRACTION_WIDTH = DisplayManager::GetWidth();
	REFRACTION_HEIGHT = DisplayManager::GetHeight();
	InitializeReflectionFrameBuffer();
	InitializeRefractionFrameBuffer();
}

WaterFrameBuffer::~WaterFrameBuffer()
{
	glDeleteFramebuffers(1, &m_ReflectionFrameBuffer);
	glDeleteTextures(1, &m_ReflectionTexture);
	glDeleteRenderbuffers(1, &m_ReflectionDepthBuffer);
	glDeleteFramebuffers(1, &m_RefractionFrameBuffer);
	glDeleteTextures(1, &m_RefractionTexture);
	glDeleteTextures(1, &m_RefractionDepthTexture);
}

void WaterFrameBuffer::InitializeRefractionFrameBuffer()
{
	m_RefractionFrameBuffer	 = CreateFrameBuffer();
	m_RefractionTexture		 = CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	m_RefractionDepthTexture = CreateDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	UnbindFrameBuffer();
}

void WaterFrameBuffer::InitializeReflectionFrameBuffer()
{
	m_ReflectionFrameBuffer = CreateFrameBuffer();
	m_ReflectionTexture		= CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	m_ReflectionDepthBuffer = CreateDepthBufferAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	UnbindFrameBuffer();
}

unsigned int WaterFrameBuffer::CreateFrameBuffer()
{
	unsigned int frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBuffer;
}

unsigned int WaterFrameBuffer::CreateTextureAttachment(const unsigned int & width, const unsigned int & height)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);
	return texture_id;
}

unsigned int WaterFrameBuffer::CreateDepthBufferAttachment(const unsigned int & width, const unsigned int & height)
{
	unsigned int depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}

unsigned int WaterFrameBuffer::CreateDepthTextureAttachment(const unsigned int & width, const unsigned int & height)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_id, 0);
	return texture_id;
}
