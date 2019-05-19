#include "Precompiled_Header_OpenGL.h"
#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ArrayID);
}

void VertexArray::BindBufferLayout(const VertexBuffer & vertexBuffer, const VertexBufferLayout & layout)
{
	Bind();
	vertexBuffer.Bind();
	unsigned offset = 0;

	const auto &elements = layout.GetElements();
	for (unsigned i = 0; i < elements.size(); ++i)
	{
		const auto &element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
