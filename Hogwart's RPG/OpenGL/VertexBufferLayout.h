#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

struct VertexBufferElement
{
	unsigned count;
	unsigned type;
	bool normalized;

	static unsigned GetSizeOfType(const unsigned &type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned>(unsigned count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
	inline const unsigned &GetStride() const { return m_Stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned m_Stride;
};

#endif // !VERTEX_BUFFER_LAYOUT_H
