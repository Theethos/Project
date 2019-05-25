#include "pch.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() :
	m_ID(0),
	m_Width(0),
	m_Height(0),
	m_ColorBufferID(0),
	m_DepthBufferID(0),
	m_Screen(nullptr)
{
	m_Projection = glm::perspective(70.0, (double)m_Width / m_Height, 1.0, 100.0);
	m_ModelView = glm::mat4(1.0);
	m_Save = glm::mat4(1.0);
}

FrameBuffer::FrameBuffer(const unsigned & w, const unsigned & h, const float & screenSize, Shader * shader, const bool & useStencil) :
	m_ID(0),
	m_Width(w),
	m_Height(h),
	m_ColorBufferID(0),
	m_DepthBufferID(0),
	m_Screen(nullptr)
{
	m_Projection = glm::perspective(70.0, (double)m_Width / m_Height, 1.0, 100.0);
	m_ModelView = glm::mat4(1.0);
	m_Save = glm::mat4(1.0);
	Load(useStencil);
	if (screenSize && shader)
		m_Screen = new Square(screenSize, *shader, m_ColorBufferID[0]);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_ID);
	glDeleteRenderbuffers(1, &m_DepthBufferID);

	for (auto & it : m_ColorBufferID)
		glDeleteTextures(1, &it);
	if (m_Screen)
		delete m_Screen;
}

bool FrameBuffer::Load(const bool & useStencil)
{
	// Check that the frame buffer has not already been created
	if (glIsFramebuffer(m_ID) == GL_TRUE)
	{
		// If so, clean the previous data
		glDeleteFramebuffers(1, &m_ID);
		for (auto & it : m_ColorBufferID)
			glDeleteTextures(1, &it);
	}

	// Generate the frame buffer
	glGenFramebuffers(1, &m_ID);

	// Bind it
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		// Create the color buffer
		m_ColorBufferID.push_back(LoadEmptyTex(m_Width, m_Height, GL_RGBA, GL_RGBA));
		// Create the render buffer
		if (useStencil)
			CreateRenderBuffer(m_DepthBufferID, GL_DEPTH24_STENCIL8);
		else 
			CreateRenderBuffer(m_DepthBufferID, GL_DEPTH_COMPONENT24);

		// Link them to the frame buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferID[0], 0);
		if (useStencil)
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);
		else	
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);

		// Check that the frame buffer has been correctly created
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			// if not, clean the data
			glDeleteFramebuffers(1, &m_ID);
			glDeleteRenderbuffers(1, &m_DepthBufferID);

			for (auto & it : m_ColorBufferID)
				glDeleteTextures(1, &it);

			std::cerr << "Can't load the FBO. Error in '" << __FILE__ << "', line " << __LINE__ << std::endl;
			return false;
		}
	// Else
	// Unbind the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	return true;
}

void FrameBuffer::StartDrawingInto()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, m_Width, m_Height);

	m_ModelView = glm::lookAt(glm::vec3(3, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	/* Add the things to draw into this frame buffer after this function */
}

void FrameBuffer::EndDrawingInto(const unsigned & w_w, const unsigned & w_h, const bool & show, const glm::vec4 & clearColor)
{
	/* Add this function after the things to draw into this frame buffer */

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

	glViewport(0, 0, w_w, w_h);

	if (show)
		m_Screen->Draw();
}

void FrameBuffer::CreateRenderBuffer(unsigned & id, const unsigned & internalFormat)
{
	if (glIsRenderbuffer(id) == GL_TRUE)
		glDeleteRenderbuffers(1, &id);

	glGenRenderbuffers(1, &id);

	glBindRenderbuffer(GL_RENDERBUFFER, id);

		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, m_Width, m_Height);	

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
