#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void BindBufferLayout(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);

	void Bind() const;
	void Unbind() const;
private:
	unsigned m_ArrayID;
};

#endif // !VERTEX_ARRAY_H
