#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
public:
	VertexBuffer(const void * data, unsigned size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned m_BufferID;
};

class IndexBuffer
{
public:
	IndexBuffer(const unsigned * data, unsigned count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline const unsigned &GetCount() const { return m_Count; }
private:
	unsigned m_BufferID;
	unsigned m_Count;
};

#endif // !VERTEX_BUFFER_H
