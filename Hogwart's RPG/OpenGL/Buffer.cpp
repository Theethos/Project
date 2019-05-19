#include "Precompiled_Header_OpenGL.h"
#include "Buffer.h"

/// /////////////////////////////////////////////////
//					VertexBuffer				   //
//\data: the actual vertices					   //
//\size: size of the vertices in BYTES			   //
/// /////////////////////////////////////////////////
VertexBuffer::VertexBuffer(const void * data, unsigned size)
{
	glGenBuffers(1, &m_BufferID);												
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/// /////////////////////////////////////////////////
//					IndexBuffer					   //
//\data: the actual indices						   //
//\count: count of indices in the data			   //
/// /////////////////////////////////////////////////
IndexBuffer::IndexBuffer(const unsigned * data, unsigned count) :
m_Count(count)
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW);
}


IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
